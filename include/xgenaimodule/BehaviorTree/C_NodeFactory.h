// ============================================================================
//  wh::xgenaimodule::BehaviorTree  —  Node-creation machinery
//  (I_NodeFactory, C_NodeFactoryImpl<TNode, TCasting>)
// ----------------------------------------------------------------------------
//  This is the template layer that turns a parsed <Node> XML element into a live
//  behavior-tree node object plus its per-instance runtime-data pool. Every node
//  type registers exactly one I_NodeFactory singleton; the engine asks that
//  factory to create node instances and to size the per-entity runtime data.
//
//  ───────────────────────  XML  ->  live object pipeline  ───────────────────
//
//   Tables/.../*.xml   <Node type="Fail"/>
//        |
//        | BT loader resolves the node-type name to its registered factory
//        v
//   I_NodeFactory* fac
//        (a C_NodeFactoryImpl<TNode, C_DefaultNodeContextCasting<TContext>>
//         singleton; one per node type)
//        |
//        | fac->CreateNode(nodeId, nodeData)              [factory virtual]
//        v
//   CreateNode (VERIFIED: sub_18142E738 for a C_Node leaf):
//        size = this->vfunc[+0x30]();          // == GetContextSize()
//        sub_1805839DC(nodeData+0x48, nodeId, size);   // record the ctx size
//        mem  = pooled_new(0x28);              // 0x28 == sizeof(C_Node leaf)
//        node = sub_181425BD0(mem);            // node ctor: installs
//               *node = node[1] = &C_NodeWrapper<C_Fail,C_Node,
//                                               S_BaseNodeContext>::vftable;
//               node[4] (=node+0x20) = 0;      // m_pCreator cleared
//        node[+0x20] = nodeData;               // m_pCreator  (C_Node +0x20)
//        node[+0x18] = nodeId;                 // m_nodeId    (C_Node +0x18)
//        return node;
//        |
//        | (a richer 0x38-node variant exists: sub_18142D848 allocates 0x38,
//        |  runs sub_18142565C — which installs a C_NodeWrapper<...> vtable —
//        |  then calls node->vfunc[+0x120](nodeData) and node->vfunc[+0x40]())
//        v
//   Tree instantiated for N entities / instances:
//        pool = C_NodeContextPool<TContext, TCasting>     (see C_NodeContext.h)
//        pool runtime-data sized by GetContextSize() (== sizeof(TContext))
//        |
//        v
//   Per tick, for instance i:
//        UpdateContext.runtimeData = &pool->GetContext(i)   (void*)
//        node->Update(runtimeData)                          [I_Node slot 17]
//             -> C_NodeWrapper forwards to TNode::Update(
//                    C_DefaultNodeContextCasting<TContext>::Cast(runtimeData))
//
//  Separation of concerns (VERIFIED):
//    * The factory (C_NodeFactoryImpl) is a per-type singleton.
//    * CreateNode installs exactly the C_NodeWrapper<TNode, TBase, TContext>
//      vtable (sub_181425BD0 installs C_NodeWrapper<C_Fail,C_Node,
//      S_BaseNodeContext>::vftable). The node behaviour TNode is the stateless
//      policy folded into that wrapper vtable (see C_NodeWrapper.h).
//    * Mutable per-instance state lives in TContext, owned by the pool — NOT in
//      the node (see C_NodeContext.h).
//
//  ── Evidence (WHGame.dll, imagebase 0x180000000) ───────────────────────────
//
//   RTTI (named symbols, confirmed via idautils.Names):
//     I_NodeFactory:
//        ??_7 `vftable'        @ 0x18231e3e8
//        ??_R0 type descriptor @ 0x182a8d680  (name string @ 0x182a8d690
//           ".?AVI_NodeFactory@BehaviorTree@xgenaimodule@wh@@")
//        ??_R4 COL             @ 0x18250c0b8
//     C_NodeFactoryImpl<C_ClearContextRelatedMessages, C_DefaultNodeContextCasting<S_BaseNodeContext>>:
//        ??_7 `vftable'        @ 0x18231cfe0
//        ??_R0 type descriptor @ 0x182a8a040  (name string @ 0x182a8a050)
//        ??_R4 COL             @ 0x18250b378
//     C_NodeFactoryImpl<C_Fail, C_DefaultNodeContextCasting<S_BaseNodeContext>>:
//        ??_7 `vftable'        @ 0x1823249e8
//        ??_R0 type descriptor @ 0x182a90c40  (name string @ 0x182a90c50)
//
//   I_NodeFactory ABSTRACT vtable @ 0x18231e3e8 — VERIFIED slot-by-slot:
//     [0] ~I_NodeFactory   0x1812edf68  (sub_1812EDF68)
//     [1..7] all == 0x180a2ca89 == _purecall  (pure virtuals)
//   => the interface declares 8 virtuals: 1 destructor + 7 pure virtuals.
//   (Adjacent ??_R4 entries in .rdata, e.g. C_NodeFactory_AbortAllAnimations,
//    are the per-node-type COLs — ~hundreds of registered node-type factories.)
//
//   CONCRETE impl vtable @ 0x18231cfe0 (ClearContextRelatedMessages) — every
//   body decompiled:
//     [0] dtor/ContextCtor 0x1812ee30c  (sub_1812EE30C)
//     [1] MakeBaseContext  0x1812ee27c  (sub_1812EE27C: builds S_BaseNodeContext)
//     [2] CreateNode       0x18142d848  (sub_18142D848: 0x38-node build path)
//     [3] MakeBaseContext2 0x1812ee2c8  (sub_1812EE2C8: S_BaseNodeContext, 0x58)
//     [4] (aux)            0x180fb9120  (sub_180FB9120) [UNVERIFIED — body is an
//             unrelated database ctor; almost certainly an interfuscator/ICF
//             mis-fold at this slot. Flagged.]
//     [5] NodeCtor         0x18142565c  (sub_18142565C: installs a
//             C_NodeWrapper<...,C_Node,...>::vftable into freshly-allocated mem)
//     [6] PoolDtor (shared) 0x18142e248 (sub_18142E248: C_NodeContextPool dtor —
//             folded; see C_NodeContext.h)
//     [7] (aux)            0x180fb9180  (sub_180FB9120) [UNVERIFIED — same fold]
//
//   NodeCtor proof (sub_181425BD0, the C_Fail factory's ctor, VERBATIM):
//       *a1    = &C_NodeWrapper<C_Fail,C_Node,S_BaseNodeContext>::`vftable';
//       a1[1]  = &C_NodeWrapper<C_Fail,C_Node,S_BaseNodeContext>::`vftable';
//       a1[4]  = 0;   // node+0x20 (m_pCreator) cleared, then set by CreateNode
//   => CreateNode builds a C_NodeWrapper over the 0x28 C_Node leaf base. The
//   creator is stored at node+0x20 and the node id at node+0x18, matching
//   C_Node's m_pCreator (+0x20) and m_nodeId (+0x18).
//
//   GetContextSize relationship: CreateNode reads the per-node context size via
//   this->vfunc[+0x30]() and records it before allocating; for the empty
//   S_BaseNodeContext the pool's GetContext uses stride 1 (see C_NodeContext.h).
//
//   [UNVERIFIED] The exact 1:1 mapping of each concrete slot to a named abstract
//   pure virtual: the concrete vtable @ 0x18231cfe0 interleaves node-build,
//   context-ctor and folded pool methods (CreateNode is at slot [2], not [0]).
//   The destructor/CreateNode/MakeContext bodies are individually verified, but
//   the abstract declaration order is reconstructed (all abstract slots are
//   _purecall, so order can only be inferred from this concrete impl).
// ============================================================================
#pragma once
#include <cstdint>
#include "../I_NoRTTITypeInfo.h"   // wh::xgenaimodule::I_NoRTTITypeInfo / I_CastableIface
#include "I_Node.h"                // I_Node (the product of CreateNode)
#include "C_Node.h"                // C_Node (0x28 leaf base built by CreateNode)
#include "C_NodeWrapper.h"         // C_NodeWrapper<TNode, TBase, TContext>
#include "C_NodeContext.h"         // S_BaseNodeContext, C_DefaultNodeContextCasting, C_NodeContextPool

namespace wh { namespace xgenaimodule { namespace BehaviorTree {

// ----------------------------------------------------------------------------
// I_NodeFactory
//   Abstract creator interface for one behavior-tree node type. One singleton is
//   registered per node type.
//
//   RTTI: .?AVI_NodeFactory@BehaviorTree@xgenaimodule@wh@@  (td @ 0x182a8d680)
//   Derives from the WH RTTI-free castable interface (I_CastableIface).
//
//   VERIFIED virtual count: 8 slots = 1 destructor + 7 pure virtuals
//   (abstract vtable @ 0x18231e3e8: slot0 dtor 0x1812edf68; slots 1..7 =
//   _purecall 0x180a2ca89). The pure-virtual SIGNATURES below are reconstructed
//   from the concrete impl vtable @ 0x18231cfe0 (each body decompiled). The
//   exact slot ORDER between abstract and concrete is reconstructed — per-slot
//   [UNVERIFIED] tags note this.
// ----------------------------------------------------------------------------
class I_NodeFactory : public wh::xgenaimodule::I_CastableIface
{
public:
    // [0] Destructor. VERIFIED abstract 0x1812edf68.
    virtual ~I_NodeFactory();

    // ----- 7 pure virtuals (slots 1..7), overridden by C_NodeFactoryImpl -----
    // [UNVERIFIED] precise slot order; reconstructed from the concrete impl.

    // Create one node instance for this type: reads the context size via the
    // size accessor, allocates the node (0x28 for a C_Node-based wrapper, 0x38
    // for richer nodes), runs the C_NodeWrapper ctor (installs
    // C_NodeWrapper<TNode,TBase,TContext>::vftable), stores creator at node+0x20
    // and nodeId at node+0x18, and returns the new I_Node*.
    // VERIFIED concrete bodies: sub_18142E738 (0x28) / sub_18142D848 (0x38).
    virtual I_Node* CreateNode(std::uint32_t nodeId, void* nodeData) = 0;

    // Returns the per-node runtime-data size used to lay out the context pool.
    // (CreateNode dispatches this as vfunc[+0x30]; == sizeof(TContext).)
    virtual std::uint32_t GetContextSize() const = 0;

    // Construct an S_BaseNodeContext-derived context object in place.
    // VERIFIED concrete bodies sub_1812EE27C / sub_1812EE2C8.
    virtual void* MakeContext(void* mem) = 0;

    // Construct the node object in place (installs the C_NodeWrapper vtable).
    // VERIFIED concrete body sub_18142565C (installs C_NodeWrapper<...>::vftable).
    virtual I_Node* ConstructNode(void* mem) = 0;

    // Allocate / own the per-entity runtime-data pool
    // (C_NodeContextPool<TContext, TCasting>*; see C_NodeContext.h).
    virtual void* CreateContextPool() = 0;

    // Returns 0 in the sampled impl. [UNVERIFIED role] VERIFIED body sub_1804380C0.
    virtual std::uint32_t GetZero() const = 0;

    // Remaining pure virtual (aux; in the sampled concrete vtable this slot is
    // an interfuscator/ICF mis-fold — see file banner). [UNVERIFIED]
    virtual void* unk_factory() = 0;
};

// ----------------------------------------------------------------------------
// C_NodeFactoryImpl<TNode, TCasting>
//   The single concrete I_NodeFactory template. One instantiation per
//   (node behaviour, context-casting policy) pair; a per-type singleton.
//
//   RTTI name pattern:
//     .?AV?$C_NodeFactoryImpl@V<TNode>@...@
//          V?$C_DefaultNodeContextCasting@U<TContext>@...@@...@@...@@
//   Verified instantiations: VC_Fail (vftable @0x1823249e8),
//   VC_ClearContextRelatedMessages (vftable @0x18231cfe0), plus
//   VC_CompanionObjectiveGate, VC_ClearInbox, VC_CompanionModeGate,
//   VC_CheckGlobalTagState, ... (one per node type).
//
//   Template parameters:
//     TNode    — stateless node behaviour policy (C_Fail, C_Wait,
//                C_ClearContextRelatedMessages, ...). Determines the
//                C_NodeWrapper<TNode, TBase, TContext> vtable installed by
//                ConstructNode and the structural base used (C_Node /
//                C_Decorator / C_Composite / ...).
//     TCasting — C_DefaultNodeContextCasting<TContext> (the default). Carries the
//                TContext whose sizeof drives GetContextSize and the pool stride.
//
//   [UNVERIFIED] object size / data members: appears stateless (per-type
//   singleton); exact sizeof not pinned in this session.
// ----------------------------------------------------------------------------
template <typename TNode,
          typename TCasting = C_DefaultNodeContextCasting<S_BaseNodeContext> >
class C_NodeFactoryImpl : public I_NodeFactory
{
public:
    using NodeLogic = TNode;
    using Casting   = TCasting;
    using Context   = typename TCasting::Context;

    ~C_NodeFactoryImpl() override;                                          // [0]
    I_Node*       CreateNode(std::uint32_t nodeId, void* nodeData) override;// sub_18142E738/D848
    std::uint32_t GetContextSize() const override;                         // == sizeof(Context)
    void*         MakeContext(void* mem) override;                         // sub_1812EE27C
    I_Node*       ConstructNode(void* mem) override;                       // sub_18142565C
    void*         CreateContextPool() override;
    std::uint32_t GetZero() const override;                                // sub_1804380C0
    void*         unk_factory() override;

    // No verified data members — appears stateless.
};

}}} // namespace wh::xgenaimodule::BehaviorTree
