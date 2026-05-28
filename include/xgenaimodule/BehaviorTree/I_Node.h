#pragma once

#include <cstdint>
#include "../I_NoRTTITypeInfo.h"

namespace wh::xgenaimodule::BehaviorTree {

// Status enum matching CryEngine BehaviorTree::Status + WH extensions
enum class E_NodeStatus : uint8_t {
    Invalid     = 0,    // not initialized
    Initialized = 1,    // ready for first update
    Running     = 2,    // actively executing
    Suspended   = 3,    // paused
    // 4 unused
    Success     = 5,    // completed successfully
    Failure     = 6,    // completed with failure
};

class I_DebugNode;

// ---------------------------------------------------------------------------
// I_Node — Warhorse BT node interface (60 virtual methods).
//
// RTTI: .?AVI_Node@BehaviorTree@xgenaimodule@wh@@
// Replaces CryEngine's BehaviorTree::INode.
// All concrete nodes instantiated via C_NodeWrapper<TNode, TBase, TContext>.
//
// Object layout (0x28 bytes):
//   +0x00: I_Node vtable (60 slots)
//   +0x08: I_DebugNode vtable (6 slots)
//   +0x10: void* m_pNodeData
//   +0x18: uint32_t m_nodeId
//   +0x1C: uint32_t _pad
//   +0x20: void* m_pCreator (cached, lazy-loaded)
// ---------------------------------------------------------------------------
class I_Node : public wh::xgenaimodule::I_CastableIface {
public:
    // ---- Identity & lifecycle [0]-[5] ----
    virtual void* GetTypeInfo() const = 0;                      // [0]  returns static type descriptor
    virtual void Destroy(uint8_t flags) = 0;                    // [1]  scalar deleting destructor
    virtual void Terminate() = 0;                               // [2]  terminate node execution
    virtual void* GetCreator() const = 0;                       // [3]  returns INodeCreator*
    virtual void* GetNodeFactory() const = 0;                   // [4]  returns INodeFactory*
    virtual I_Node* Clone() = 0;                                // [5]  deep-copy (allocs 0x28)

    // ---- Node type & child management [6]-[9] ----
    virtual const char* GetNodeCategory() const = 0;            // [6]  "Decorator"/"Composite"/"Gate" — purecall in leaf
    virtual uint32_t GetNodeId() const = 0;                     // [7]  returns m_nodeId
    virtual void SetNodeId(uint32_t id) = 0;                    // [8]  writes m_nodeId
    virtual int32_t GetChildCount() const = 0;                  // [9]  purecall in leaf

    // ---- Node properties [10]-[11] ----
    virtual bool IsAction() const = 0;                          // [10] false in base
    virtual void unk_11() = 0;                                  // [11] guard_nop

    // ---- Child execution [12]-[13] ----
    virtual void TickChild() = 0;                               // [12] tick child with factory lookup
    virtual void TerminateChild() = 0;                          // [13] cleanup child resources

    // ---- Callbacks (overridden by concrete nodes) [14]-[15] ----
    virtual void OnInitialize(void* context) = 0;               // [14]
    virtual void OnTerminate(void* context) = 0;                // [15]

    // ---- Child state queries [16]-[17] ----
    virtual E_NodeStatus GetChildStatus() const = 0;            // [16] reads child runtime status
    virtual E_NodeStatus Update(void* context) = 0;             // [17] returns Status

    // ---- Child lifecycle [18]-[22] ----
    virtual void ResetChild() = 0;                              // [18] status→Invalid, terminate
    virtual void StartChild() = 0;                              // [19] status→Initialized, initialize
    virtual E_NodeStatus CompleteNode() = 0;                    // [20] status→Success/Failure
    virtual E_NodeStatus TickNode(void* context) = 0;           // [21] main state machine tick
    virtual E_NodeStatus UpdateNode(void* context) = 0;         // [22] calls OnUpdate, check completion

    // ---- Context data [23]-[24] ----
    virtual void* GetContextData() = 0;                         // [23]
    virtual void SetContextData(void* data) = 0;                // [24]

    // ---- Suspend/Resume [25]-[26] ----
    virtual E_NodeStatus SuspendNode() = 0;                     // [25] status→Suspended, calls OnSuspend
    virtual E_NodeStatus ResumeNode(void* context) = 0;         // [26] calls OnResume

    // ---- Loading [27]-[28] ----
    virtual void LoadFromXml(void* xmlNode, void* loadCtx) = 0; // [27]
    virtual void ForceTerminate() = 0;                          // [28] calls OnAbort, fail, complete

    // ---- Queries [29]-[32] ----
    virtual bool IsValid() const = 0;                           // [29] returns true in base
    virtual int32_t unk_30() const = 0;                         // [30]
    virtual bool IsLeaf() const = 0;                            // [31] returns false in base
    virtual void unk_32() = 0;                                  // [32]

    // ---- Events [33]-[34] ----
    virtual void SendEvent(void* evtCtx, void* event) = 0;     // [33]
    virtual void SetNodeData(void* data) = 0;                   // [34] writes m_pNodeData (+0x10)

    // ---- Attributes [35]-[36] ----
    virtual void* GetNodeAttributes() const = 0;                // [35] lazy-load, cached at +0x20
    virtual void unk_36() = 0;                                  // [36]

    // ---- Event handling [37]-[39] ----
    virtual void HandleEvent(void* ctx, void* event) = 0;       // [37]
    virtual void unk_38() = 0;                                  // [38]
    virtual E_NodeStatus Tick(void* updateCtx) = 0;             // [39] main entry point

    // ---- Additional queries [40]-[46] ----
    virtual void unk_40() = 0;                                  // [40] differs per base
    virtual void unk_41() = 0;                                  // [41]
    virtual void unk_42() = 0;                                  // [42]
    virtual int32_t unk_43() const = 0;                         // [43]
    virtual bool unk_44() const = 0;                            // [44] returns false
    virtual void unk_45() = 0;                                  // [45] nop
    virtual int32_t GetNodeTypeId() const = 0;                  // [46]

    // ---- Child lifecycle callbacks [47]-[52] ----
    // guard_nop in C_Node (leaf); overridden by Decorator/Composite
    virtual void OnChildInitialized() = 0;                      // [47]
    virtual void OnFirstUpdate(void* context) = 0;              // [48]
    virtual void OnUpdate(void* context) = 0;                   // [49]
    virtual void OnRunning(void* context) = 0;                  // [50]
    virtual void OnSuspended(void* context) = 0;                // [51]
    virtual void OnCompleted() = 0;                             // [52]

    // ---- Child control [53]-[56] ----
    virtual void TerminateChildren() = 0;                       // [53] guard_nop in leaf
    virtual void ForceFailChild() = 0;                          // [54] sets child status=Failure
    virtual void unk_55() = 0;                                  // [55]
    virtual void unk_56() = 0;                                  // [56]

    // ---- Suspend/Abort callbacks [57]-[59] ----
    virtual void OnSuspend() = 0;                               // [57]
    virtual void OnResume() = 0;                                // [58]
    virtual void OnAbort() = 0;                                 // [59]
};

}  // namespace wh::xgenaimodule::BehaviorTree
