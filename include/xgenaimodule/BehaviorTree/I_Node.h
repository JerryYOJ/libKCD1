#pragma once

#include <cstdint>
#include "../I_NoRTTITypeInfo.h"

namespace wh::xgenaimodule::BehaviorTree {

// ===========================================================================
// E_NodeStatus — per-node execution status (VERIFIED 2026-06, core-engine RE).
//
// Stored as a single byte at runtimeData+0x08 (NOT in the node object). Values
// read directly from the binary's byte stores/compares:
//   slot20 SetResult : status==1 -> 5 (Success), else -> 6 (Failure)
//   slot17 IsRunning : (status-1)<=2  -> {1,2,3}
//   terminal test    : (status-5)<=1  -> {5,6}
//   slot25 Abort     : status -> 3, then abort hook sets -> 4
// ===========================================================================
enum class E_NodeStatus : uint8_t {
    None     = 0,   // reset / not active (slot18 OnEnter writes this)
    Running  = 1,   // active, canonical (slot19 Activate writes this)
    Running2 = 2,   // running sub-state (slot21 case 2 -> hook +0x190)
    Running3 = 3,   // running/aborting sub-state (slot25 Abort writes this)
    Aborted  = 4,   // interrupted/cancelled — NOT running and NOT terminal
    Success  = 5,   // terminal success
    Failure  = 6,   // terminal failure
};
constexpr bool IsRunning (E_NodeStatus s) { return (uint8_t)((uint8_t)s - 1) <= 2; } // {1,2,3}
constexpr bool IsTerminal(E_NodeStatus s) { return (uint8_t)((uint8_t)s - 5) <= 1; } // {5,6}

class I_DebugNode;

// ===========================================================================
// I_Node — Warhorse BT node interface (70 virtual slots).
//
// RTTI: .?AVI_Node@BehaviorTree@xgenaimodule@wh@@  (replaces CryEngine INode).
// All concrete nodes are instantiated via C_NodeWrapper<TNode, TBase, TContext>.
//
// VTABLE / SLOT MAP — VERIFIED 2026-06 by the core-engine RE (disasm of the
// COL-certified clean C_Node base vtable, C_AddBuff primary @0x182211490; slot
// order is consistent across nodes — 55/60 leaf slots are byte-identical, so a
// shared slot maps to the same method in every node). Slot index N is dispatched
// at vtable byte offset N*8. CryEngine interfuscator shuffles the slot ORDER but
// consistently per-interface, so the offsets below are the source of truth.
// Confidence is tagged per method; [UNVERIFIED] entries are honest placeholders.
//
// OBJECT LAYOUT (0x28 bytes, VERIFIED):
//   +0x00 I_Node primary vptr (70 slots)
//   +0x08 I_DebugNode vptr
//   +0x10 void*    m_pNodeData    parsed/static node-definition (slot32/33/34)
//   +0x18 uint32_t m_nodeId       (slot7/8)
//   +0x1C uint32_t _pad
//   +0x20 void*    m_pCreator     LAZILY-CACHED creator/owning-context: set by
//                                  slot35 GetCreator from m_pNodeData->vfn[+0x118];
//                                  GetRuntimeData() == m_pCreator[+0x48][m_nodeId],
//                                  GetTree() == m_pCreator[+0x78].
//
// RUNTIME-DATA MODEL: a node's per-tick state is NOT in the node — it lives in an
// S_NodeRuntimeData record (status byte @+0x08) allocated only while the node is
// active. The records sit in the creator's array (creator+0x48 begin .. +0x50
// end, indexed by m_nodeId); slot12 AcquireRuntimeData allocs one from an
// FNV-1a-keyed global pool (basis 0xCBF29CE484222325, prime 0x100000001B3),
// slot13 ReleaseRuntimeData frees+NULLs it.
//
// TICK FSM (VERIFIED): slot21 Update is the per-frame entry — if no runtime data
// or status None it Activates (slot19 -> Running), else dispatches the per-status
// hook (+0x180/+0x190/+0x198) with the UpdateContext, then SetResult (slot20 ->
// Success/Failure) once terminal. Composites/decorators drive children via slot22
// -> StartChild (slot49 +0x188), which copies the child's status (slot16) up.
//
// The XML loader is NOT a slot here — it is the factory path (factory slot5
// CreateAndLoad -> node SetCreator(slot36 +0x120) -> node LoadFromXml(slot14
// +0x70)); see C_NodeFactory.h.
// ===========================================================================
class I_Node : public wh::xgenaimodule::I_CastableIface {
public:
    // ---- Identity / lifecycle [0]-[5] ----
    virtual const void* GetTypeInfo() const = 0;                // [0]  override returns a static type/category blob [UNVERIFIED exact]
    virtual void  Destroy(uint8_t flags) = 0;                   // [1]  +0x08 VERIFIED scalar/vector deleting dtor; if(flags&1) free 0x28; sets both vptrs
    virtual int64_t vfn2() = 0;                                 // [2]  [UNVERIFIED] base returns 0
    virtual void* vfn3() = 0;                                   // [3]  [UNVERIFIED] returns *(GetTree()+0x30) (owner/parent?)
    virtual void* GetTree() const = 0;                          // [4]  +0x20 VERIFIED -> GetCreator()[+0x78] (tree-instance/blackboard root)
    virtual I_Node* CreateInstance() = 0;                       // [5]  override = the node's create/clone thunk (alloc 0x28 + ctor)

    // ---- Node type / child count [6]-[9] ----
    virtual const char* GetNodeCategory() const = 0;            // [6]  ABSTRACT (purecall in leaf): "Decorator"/"Composite"/"Gate"
    virtual uint32_t GetNodeId() const = 0;                     // [7]  +0x38 VERIFIED return m_nodeId(+0x18)
    virtual void     SetNodeId(uint32_t id) = 0;                // [8]  +0x40 VERIFIED m_nodeId(+0x18)=id
    virtual int32_t  GetChildCount() const = 0;                 // [9]  ABSTRACT (purecall in leaf)

    // ---- Structure predicate / runtime-data lifecycle [10]-[13] ----
    virtual bool IsComposite() const = 0;                       // [10] +0x50 VERIFIED base=false; gates leaf acquire/release [name medium]
    virtual void vfn11() = 0;                                   // [11] [UNVERIFIED] nop in base
    virtual void AcquireRuntimeData() = 0;                      // [12] +0x60 VERIFIED alloc per-node runtime data from FNV pool -> creator[+0x48][id]
    virtual void ReleaseRuntimeData() = 0;                      // [13] +0x68 VERIFIED free+NULL the runtime data

    // ---- Per-node load/bind & terminate hooks [14]-[15] (node-specific override) ----
    virtual bool LoadFromXml(void* xmlNode, void* loadDesc) = 0;// [14] +0x70 VERIFIED(RemoveItem) parse XML attrs + bind NodeAttribute<T>/variables
    virtual void OnTerminate(void* context) = 0;                // [15] [UNVERIFIED] node-specific (AddBuff: bound-variable counterpart)

    // ---- Status / tick state machine [16]-[28] (VERIFIED unless noted) ----
    virtual E_NodeStatus GetStatus() const = 0;                 // [16] +0x80 read runtimeData->status(+0x08), bounds-checked; else None
    virtual bool         IsRunning() const = 0;                 // [17] +0x88 (status-1)<=2
    virtual bool         OnEnter() = 0;                         // [18] +0x90 Reset: status->None; reset-children hook +0x1A8; if !composite Release
    virtual bool         Activate() = 0;                        // [19] +0x98 acquire RD if !composite; status->Running; leaf-work hook +0x178; finish if terminal
    virtual E_NodeStatus SetResult() = 0;                       // [20] +0xA0 status==Running?Success:Failure; on-finish hook +0x1A0
    virtual E_NodeStatus Update(void* pUpdateCtx) = 0;          // [21] +0xA8 MAIN per-frame tick: dispatch per status, then SetResult when terminal
    virtual E_NodeStatus UpdateChild(void* pUpdateCtx) = 0;     // [22] +0xB0 StartChild(slot49) then SetResult; child->parent status propagation
    virtual bool         vfn23() = 0;                           // [23] +0xB8 [UNVERIFIED] transition: status->2 + hook +0x1B0
    virtual E_NodeStatus vfn24(void* pUpdateCtx) = 0;           // [24] +0xC0 [UNVERIFIED] tick via hook +0x1B8
    virtual E_NodeStatus Abort() = 0;                           // [25] +0xC8 status->Running3(3); abort hook +0x1C8 (default sets Aborted=4)
    virtual E_NodeStatus vfn26(void* pUpdateCtx) = 0;           // [26] +0xD0 [UNVERIFIED] tick via hook +0x1D0 (abort continuation?)
    virtual bool         StartChildExecution(void* pReq) = 0;   // [27] +0xD8 VERIFIED runtime child scheduling (NOT XML load): status->Running, link child-exec entry
    virtual bool         ForceFailure() = 0;                    // [28] +0xE0 hook +0x1D8; status->Failure; SetResult

    // ---- Misc queries [29]-[31] ----
    virtual int32_t vfn29() const = 0;                          // [29] [UNVERIFIED]
    virtual int32_t vfn30() const = 0;                          // [30] [UNVERIFIED]
    virtual bool    vfn31() const = 0;                          // [31] [UNVERIFIED] base=false (shares slot10 body)

    // ---- Node-data / creator accessors [32]-[36] (VERIFIED) ----
    virtual void* GetNodeDataRaw() = 0;                         // [32] +0x100 return this+0x10
    virtual void* GetNodeData() = 0;                            // [33] +0x108 virtual forwarder to slot32
    virtual void  SetNodeData(void* data) = 0;                  // [34] +0x110 this+0x10 = data
    virtual void* GetCreator() = 0;                             // [35] +0x118 cached this+0x20, else m_pNodeData->vfn[+0x118]
    virtual void  SetCreator(void* creator) = 0;                // [36] +0x120 this+0x20 = creator

    // ---- Entity / debug / script context [37]-[42] (call shapes verified; identities medium) ----
    virtual uint32_t    GetEntityId() const = 0;                // [37] +0x128 wraps GetEntity, returns Entity+0x8 [medium]
    virtual void*       GetEntity() const = 0;                  // [38] +0x130 GetCreator()[+0x78] -> +8 -> +0x18 -> +8 IEntity [medium]
    virtual const char* GetDebugName() const = 0;               // [39] +0x138 entity name, else "UKNOWN HOST NAME" literal [medium]
    virtual void        vfn40() = 0;                            // [40] [UNVERIFIED] (AddBuff: builds silent var-ref bindings)
    virtual bool        PushEntityScriptContext() = 0;          // [41] +0x148 push Lua 'entity'/'data' tables [medium]
    virtual bool        PopEntityScriptContext() = 0;           // [42] +0x150 pop them, write back bound C_Variable results [medium]

    // ---- [43]-[46] [UNVERIFIED] ----
    virtual int32_t vfn43() const = 0;                          // [43] [UNVERIFIED]
    virtual bool    vfn44() const = 0;                          // [44] [UNVERIFIED] base=false
    virtual void    vfn45() = 0;                                // [45] [UNVERIFIED] nop
    virtual int32_t vfn46() const = 0;                          // [46] [UNVERIFIED] GetNodeTypeId?

    // ---- Overridable execution hooks [47]-[53] (nop in leaf base; the FSM calls these) ----
    virtual void         OnLeafWork(void* ctx) = 0;             // [47] +0x178 leaf work, invoked by Activate(slot19)
    virtual E_NodeStatus OnUpdateRunning(void* ctx) = 0;        // [48] +0x180 per-status hook (status 1), invoked by Update(slot21)
    virtual E_NodeStatus StartChild(void* pUpdateCtx) = 0;      // [49] +0x188 VERIFIED tick child, copy child status into this->status
    virtual E_NodeStatus OnUpdateRunning2(void* ctx) = 0;       // [50] +0x190 per-status hook (status 2)
    virtual E_NodeStatus OnUpdateRunning3(void* ctx) = 0;       // [51] +0x198 per-status hook (status 3)
    virtual void         OnFinish() = 0;                        // [52] +0x1A0 on-finish hook (invoked by SetResult/Activate)
    virtual void         ResetChildren() = 0;                   // [53] +0x1A8 reset finished children hook (invoked by OnEnter)

    // ---- Direct status setters / more hooks [54]-[59] ----
    virtual void SetStatusFailure() = 0;                        // [54] +0x1B0 VERIFIED runtimeData->status = Failure(6)
    virtual void vfn55() = 0;                                   // [55] [UNVERIFIED] nop
    virtual void vfn56() = 0;                                   // [56] [UNVERIFIED] nop (+0x1C0)
    virtual void SetStatusAborted() = 0;                        // [57] +0x1C8 VERIFIED runtimeData->status = Aborted(4) — default abort hook
    virtual void vfn58() = 0;                                   // [58] [UNVERIFIED] nop (+0x1D0)
    virtual void OnForceFailure() = 0;                          // [59] +0x1D8 [UNVERIFIED] hook invoked by ForceFailure(slot28)

    // ---- Tail hooks/predicates [60]-[69] ([UNVERIFIED]; mostly nop/default) ----
    virtual bool    vfn60() = 0;                                // [60] [UNVERIFIED] base=false
    virtual void    vfn61() = 0;                                // [61] [UNVERIFIED]
    virtual void    vfn62() = 0;                                // [62] [UNVERIFIED] nop
    virtual void    OnCreated() = 0;                            // [63] +0x1F8 [medium] derived OnCreated hook (invoked by AcquireRuntimeData)
    virtual void    vfn64() = 0;                                // [64] [UNVERIFIED]
    virtual void    vfn65() = 0;                                // [65] [UNVERIFIED]
    virtual void    vfn66() = 0;                                // [66] [UNVERIFIED]
    virtual void    vfn67() = 0;                                // [67] [UNVERIFIED]
    virtual void    vfn68() = 0;                                // [68] [UNVERIFIED]
    virtual void    vfn69() = 0;                                // [69] [UNVERIFIED] nop (last slot; next .rdata qword is the neighbouring vtable's COL)
};

}  // namespace wh::xgenaimodule::BehaviorTree
