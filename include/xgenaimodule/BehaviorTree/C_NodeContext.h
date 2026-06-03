// ============================================================================
//  wh::xgenaimodule::BehaviorTree  —  Per-entity runtime-data layer
//  (S_BaseNodeContext, C_DefaultNodeContextCasting<TContext>,
//   C_NodeContextPool<TContext, TCasting>)
// ----------------------------------------------------------------------------
//  KCD behavior-tree nodes are STATELESS and SHARED across every entity / tree
//  instance that runs the same compiled tree (see C_NodeWrapper.h). The node
//  object itself (a 0x28 C_Node leaf, etc.) holds NO per-tick mutable state. All
//  mutable state lives in a TContext struct owned by a per-node
//  C_NodeContextPool, one TContext slot per behavior-tree instance.
//
//  At runtime a node receives its context as an opaque `void* runtimeData`
//  (UpdateContext.runtimeData = a pointer into the pool array) and turns it back
//  into a strongly-typed TContext& via the compile-time policy
//  C_DefaultNodeContextCasting<TContext>.
//
//  XML -> live object pipeline: see C_NodeFactory.h for the full diagram.
//
//  ── Evidence (WHGame.dll, imagebase 0x180000000) — canonical instantiation
//     C_NodeContextPool<S_BaseNodeContext, C_DefaultNodeContextCasting<...>> ────
//
//   RTTI (named symbols, confirmed via idautils.Names):
//     S_BaseNodeContext  ??_R0 type descriptor   @ 0x182a8d1c0
//        ".?AUS_BaseNodeContext@BehaviorTree@xgenaimodule@wh@@"  (a 'struct')
//        S_BaseNodeContext `vftable'              @ (referenced by context ctors;
//        e.g. installed by sub_1812EE27C)         — see note below
//     C_NodeContextPool<S_BaseNodeContext,...>:
//        ??_7 `vftable'         @ 0x18231b300
//        ??_R0 type descriptor  @ 0x182a89f70  (name string @ 0x182a89f80)
//        ??_R4 COL              @ 0x18250b350  (vftable[-8])
//
//   C_NodeContextPool vtable @ 0x18231b300 — 8 slots, every body decompiled:
//     [0] ~dtor               0x18142e248  (sub_18142E248):
//             *this = &C_NodeContextPool::vftable;
//             if (m_pContexts) operator_delete(m_pContexts);
//             m_pContexts = 0;  m_count = 0;             // (+0x08 ptr, +0x10 u32)
//             if (flags & 1) operator_delete(this);      // scalar-deleting dtor
//     [1] AllocateNode/Create 0x18142e738  (sub_18142E738):
//             size = this->factory_vfunc[+0x30]();        // GetContextSize()
//             record size at (a3+0x48); mem = pooled_new(0x28);
//             node = sub_181425BD0(mem);                  // node ctor (see below)
//             node[+0x20] = a3;  node[+0x18] = a2;        // m_pCreator, m_nodeId
//             (NOTE: this is folded with the FACTORY's CreateNode — the pool and
//              factory vtables share this 0x28-node-build body.)
//     [2] MakeBaseContext     0x1812ee27c  (sub_1812EE27C):
//             constructs an S_BaseNodeContext in place (installs its vftable);
//             scalar-deleting variant frees 0x78 bytes.
//     [3] (returns 0)         0x1804380c0  (sub_1804380C0: `return 0;`)
//     [4] GetContext          0x18142e6b8  (sub_18142E6B8):
//             return m_pContexts ? (m_pContexts + index) : 0;   // STRIDE 1
//     [5] GetContext (dup)    0x18142e668  (folds to sub_18142E6B8, same body)
//     [6] _purecall           0x180a2ca89
//     [7] _purecall           0x180a2ca89
//
//   GetContext (slots [4]/[5]) adds the raw `index` to m_pContexts with NO
//   scaling => element stride == 1 => sizeof(S_BaseNodeContext) == 1 (empty).
//   The factory's alignment accessor (sub_1812EE2A8) likewise resolves to the
//   empty-context size class (see C_NodeFactory.h).
//
//   AllocateContext / growth: the dtor's free of m_pContexts and the
//   _InterlockedExchangeAdd-tracked pooled allocator in the Create path are the
//   only allocation sites seen; a separate "AllocateContext(count)" was NOT
//   isolated as its own slot in this vtable (slots [4]/[5] are read-only index
//   accessors). [UNVERIFIED] whether the count-allocating entry lives behind a
//   different (non-folded) instantiation.
//
//   C_DefaultNodeContextCasting<TContext> is a stateless, header-only policy:
//   no standalone code, no data members. The cast is fully inlined at every node
//   Update/OnInitialize call site (runtimeData passed as void* and used directly
//   as TContext*).
//
//  ── EXECUTION-STATE / STATUS model (core-engine RE 2026-06, see I_Node.h) ────
//   A node's per-instance EXECUTION STATUS is a single E_NodeStatus byte read by
//   I_Node::GetStatus (slot16) from runtimeData+0x08, where
//       runtimeData = GetCreator()->[+0x48][m_nodeId]
//   i.e. the creator/tree-instance owns an array of per-node runtime records at
//   +0x48 (begin) .. +0x50 (end), indexed by m_nodeId; I_Node::AcquireRuntimeData
//   (slot12) allocates a record from an FNV-1a-keyed global pool on node enter and
//   ReleaseRuntimeData (slot13) frees it on leave. GetTree (slot4) returns
//   creator->[+0x78] (the tree-instance/blackboard root).
//   [OPEN/UNVERIFIED] reconciliation: it is NOT yet proven whether this creator
//   +0x48 runtime-record array is the SAME storage as a node's
//   C_NodeContextPool::m_pContexts (the TContext gameplay-state pool below) or a
//   SEPARATE engine-managed status array. Evidence pulls both ways: some TContext
//   types (e.g. S_AddBuffContext) carry a status byte at +0x08 matching the
//   runtime record, yet C_NodeContextPool<S_BaseNodeContext> has stride 1 (no room
//   for a status byte). Treat "TContext" (gameplay state, pooled here) and
//   "runtime record" (status@+0x08, creator+0x48) as possibly-distinct until the
//   GetContextSize→pool wiring vs the slot12 FNV pool are traced to a common base.
// ============================================================================
#pragma once
#include <cstdint>
#include "../I_NoRTTITypeInfo.h"   // wh::xgenaimodule::I_NoRTTITypeInfo / I_CastableIface

namespace wh { namespace xgenaimodule { namespace BehaviorTree {

// ----------------------------------------------------------------------------
// S_BaseNodeContext
//   Base of every per-(tree-instance) behavior-tree node runtime context.
//
//   RTTI: .?AUS_BaseNodeContext@BehaviorTree@xgenaimodule@wh@@  (a 'struct';
//         type descriptor @ 0x182a8d1c0). It HAS a vftable in the binary (the
//         context hierarchy is polymorphic; the base ctor sub_1812EE27C installs
//         S_BaseNodeContext::`vftable'), but it carries no data members of its
//         own beyond that vptr footprint at the empty-struct stride.
//
//   VERIFIED EMPTY-stride: the pool's GetContext (sub_18142E6B8 @ 0x18142e6b8)
//   indexes with stride 1 (`m_pContexts + index`), so the per-element size for
//   this pool is 1 byte.
//
//   Derived contexts (S_WaitContext, S_LoopContext, S_SwitchBaseContext,
//   S_FixedNumberOfSelectionsContext, ...) add per-node tick state and raise the
//   pool element stride to their own sizeof.
//
//   [UNVERIFIED] Whether S_BaseNodeContext is truly polymorphic in source (it
//   has a vftable) vs. only via the folded ctor. Declared as a plain empty
//   struct here, matching the 1-byte stride; flagged for follow-up.
// ----------------------------------------------------------------------------
struct S_BaseNodeContext
{
    // No data members (per-element stride is 1 byte for this pool).
};
static_assert(sizeof(S_BaseNodeContext) == 1,
    "empty per-element stride: pool GetContext sub_18142E6B8 indexes with stride 1");

// ----------------------------------------------------------------------------
// C_DefaultNodeContextCasting<TContext>
//   Stateless compile-time policy: the default 2nd template argument of both
//   C_NodeFactoryImpl and C_NodeContextPool. Converts the opaque per-tick
//   `void* runtimeData` (a pool element) into a typed TContext&.
//
//   RTTI name fragment (spelled out in the pool/factory template names):
//     ?$C_DefaultNodeContextCasting@U<TContext>@BehaviorTree@xgenaimodule@wh@@
//
//   Emits NO standalone code and has NO data members: every use is inlined.
//   [UNVERIFIED] exact member-function name(s) — folded away, no symbol remains.
// ----------------------------------------------------------------------------
template <typename TContext>
class C_DefaultNodeContextCasting
{
public:
    using Context = TContext;

    // Turn the pool's raw runtime-data pointer into a typed context reference.
    static TContext&       Cast(void* runtimeData) noexcept
    {
        return *static_cast<TContext*>(runtimeData);
    }
    static const TContext& Cast(const void* runtimeData) noexcept
    {
        return *static_cast<const TContext*>(runtimeData);
    }
    // No data members (stateless policy).
};

// ----------------------------------------------------------------------------
// C_NodeContextPool<TContext, TCasting>
//   Owns the per-tree-instance TContext runtime-data slots for a single node.
//   Created per node by the node's I_NodeFactory (see C_NodeFactory.h).
//
//   Object layout (VERIFIED from the dtor sub_18142E248):
//     +0x00  vptr
//     +0x08  TContext*     m_pContexts   (runtime-data block; null when empty)
//     +0x10  std::uint32_t m_count       (number of contexts)
//
//   Derives from the WH RTTI-free castable interface (I_CastableIface) — modeled
//   via inheritance, NO raw vtable pointers.
//
//   Validated vtable @ 0x18231b300 (slots decoded in the file banner).
// ----------------------------------------------------------------------------
template <typename TContext, typename TCasting = C_DefaultNodeContextCasting<TContext> >
class C_NodeContextPool : public wh::xgenaimodule::I_CastableIface
{
public:
    virtual ~C_NodeContextPool();                                  // [0] 0x18142e248

    // [1] Build a node instance bound to this pool (folded with the factory's
    //     CreateNode; allocates a 0x28 C_Node leaf via sub_181425BD0).
    //     a2 = nodeId, a3 = creator(stored at node+0x20). Returns the node.
    virtual I_NoRTTITypeInfo* CreateNode(std::uint32_t nodeId, void* creator); // 0x18142e738

    // [2] Construct an S_BaseNodeContext-derived context in place.
    virtual void* MakeContext();                                  // [2] 0x1812ee27c

    // [3] Returns 0 (sub_1804380C0).  [UNVERIFIED role]
    virtual std::uint32_t GetZero() const;                        // [3] 0x1804380c0

    // [4]/[5] Indexed runtime-data access: returns &m_pContexts[index]
    //         (stride == sizeof(TContext); 1 for S_BaseNodeContext).
    virtual TContext* GetContextPtr(std::uint32_t index);        // [4]/[5] 0x18142e6b8

    // Resolve one instance's runtime data through the casting policy.
    // (header-only convenience; inlined at the engine call sites)
    TContext& GetContext(std::uint32_t index)
    {
        return TCasting::Cast(GetContextPtr(index));
    }

    TContext*     m_pContexts;  // +0x08  array[m_count]; null when empty
    std::uint32_t m_count;      // +0x10  (+0x14 padding)
};

}}} // namespace wh::xgenaimodule::BehaviorTree
