#pragma once

#include <cstdint>
#include "C_Node.h"
#include "C_Decorator.h"
#include "C_NodeWrapper.h"

// ===========================================================================
// C_Barrier.h  -  BT "barrier" decorators (ExecutionBarrier / PassiveBarrier /
//                 NPCPassiveBarrier).
//
// Reverse-engineered from WHGame.dll (KCD1 retail).  Namespace
// wh::xgenaimodule::BehaviorTree.
//
// A barrier is a single-child decorator that GATES execution of its child
// subtree.  The three barriers form an inheritance chain (each refines the
// previous), VERIFIED from their RTTI ClassHierarchyDescriptor base-class
// arrays (resolved via signature-validated COLs).
//
// VERIFIED anchors (name-string / primary vtable / I_DebugNode secondary vtable
//                   [object+0x08] / ctor):
//   C_ExecutionBarrier  name@0x182a88e50  primaryVT@0x1821e2e28  debugVT@0x1821e2df0
//                       ctor sub_18068B2F8
//   C_PassiveBarrier    name@0x182a88ea0  primaryVT@0x1821e2940  debugVT@0x1821e2908
//                       ctor sub_18068B250  (chains the Exec ctor)
//   C_NPCPassiveBarrier name@0x182a88d00  primaryVT@0x18221c008  debugVT@0x18221bfd0
//                       ctor sub_1806ECEA8  (chains the Passive ctor)
//                       (plain "NPCPassiveBarrier" string also @0x18231ab28)
//
// VERIFIED RTTI base-class arrays (in order):
//   C_ExecutionBarrier :
//       C_NodeWrapper<C_ExecutionBarrier, C_Decorator, S_ExecutionBarrierContext>
//       : C_Decorator : C_Node : I_Node : I_CastableIface : I_NoRTTITypeInfo
//       : I_DebugNode
//   C_PassiveBarrier :
//       C_NodeWrapper<C_PassiveBarrier, C_ExecutionBarrier, S_PassiveBarrierContext>
//       : C_ExecutionBarrier
//       : C_NodeWrapper<C_ExecutionBarrier, C_Decorator, S_ExecutionBarrierContext>
//       : C_Decorator : C_Node : I_Node : ...
//   C_NPCPassiveBarrier :
//       C_NodeWrapper<C_NPCPassiveBarrier, C_PassiveBarrier, S_NPCPassiveBarrierContext>
//       : C_PassiveBarrier
//       : C_NodeWrapper<C_PassiveBarrier, C_ExecutionBarrier, S_PassiveBarrierContext>
//       : C_ExecutionBarrier
//       : C_NodeWrapper<C_ExecutionBarrier, C_Decorator, S_ExecutionBarrierContext>
//       : C_Decorator : C_Node : I_Node : ...
//
// So (VERIFIED):
//   C_NPCPassiveBarrier -> C_PassiveBarrier -> C_ExecutionBarrier -> C_Decorator
//   (single child), each step wrapped through a
//   C_NodeWrapper<Self, ImmediateBarrierBase, SelfContext> instantiation.  The
//   context type names S_ExecutionBarrierContext / S_PassiveBarrierContext /
//   S_NPCPassiveBarrierContext come straight from the wrapper manglings - so
//   those identities are VERIFIED (field layouts are not).
//
// VERIFIED OBJECT SIZE = 0x30 (== sizeof(C_Decorator); NO own data member)
// --------------------------------------------------------------------------
// All three barriers are 0x30 bytes and add NO member beyond C_Decorator.
// Evidence (two independent oracles agree, 2026-05 re-derivation):
//   1. SCALAR DELETING DTOR: slot 1 of all three primary vtables is the shared
//      sub_1801FD350, which does `operator delete(this, 0x30)`.
//   2. CREATE-THUNK double-confirm via a concrete derived node: the
//      C_CompanionObjectiveGate create thunk sub_1806ECD6C does
//          p = alloc(0x30, &v);
//          _InterlockedExchangeAdd(&dword_183002E60, 0x30u);   // accounting add
//          ctor sub_1806ECDE4(p, xml);                          // chains the NPC ctor
//      i.e. operator new(0x30) AND the 0x30 accounting add (double-confirm).
//      C_CompanionObjectiveGate adds no member over C_NPCPassiveBarrier, so the
//      full NPC barrier object is 0x30; the chain adds nothing => all 0x30.
//   3. 0x30 == sizeof(C_Decorator) (independently verified, same as C_Loop).
//
//   LAYOUT (== C_Decorator, no extra field):
//     +0x00 primary vtable
//     +0x08 I_DebugNode vtable
//     +0x10 void*   m_pNodeData     (C_Node)
//     +0x18 uint32  m_nodeId        (C_Node)
//     +0x1C uint32  _pad
//     +0x20 void*   m_pCreator      (C_Node)
//     +0x28 I_Node* m_pChild        (C_Decorator single child)
//   (= 0x30 total)
//
// CORRECTION (2026-05): a prior draft asserted these were 0x38 with a
//   `uint64 m_barrierState @ +0x30` and cited "create thunks sub_18068B2C8 /
//   sub_18068B268 / sub_1806ECEC0 - all MemAlloc(0x38)". BOTH were WRONG:
//     * Those three addresses are not create thunks - they are the ctors
//       (sub_18068B250 Passive / sub_1806ECEA8 NPC and their interior offsets);
//       they contain NO malloc (they take a pre-allocated `this`, set the
//       wrapper-then-concrete vtables, and copy a runtime variable-reference
//       table). The allocator is the create thunk a level up (sub_1806ECD6C for
//       the NPC-derived companion gate, etc.).
//     * The deleting dtor frees 0x30, not 0x38, and no ctor writes a member at
//       +0x30 - the m_barrierState field did not exist (same fabrication pattern
//       as the composites' bogus cached child-count). It has been removed.
//
// INSTANTIATION NOTE: the three barriers are used almost entirely as BASE
// classes; the concrete BT nodes that actually get allocated are derived
// wrappers, e.g. C_LockNode<C_ExecutionBarrier> (ctor sub_18068B1CC),
// C_CompanionObjectiveGate (ctor sub_1806ECDE4, create thunk sub_1806ECD6C),
// and C_CompanionModeGate - each of which adds no data member, hence the 0x30
// barrier object size is the size those concrete nodes allocate.
//
// WHAT EACH GATES ON  [partially UNVERIFIED]
// ------------------------------------------
//   C_ExecutionBarrier : base barrier - gates the child on an execution
//       predicate (S_ExecutionBarrierContext); the structural building block
//       for the passive variants.
//   C_PassiveBarrier   : refines ExecutionBarrier so the child runs only while
//       the owner is "passive" (not actively pursuing its goal).
//   C_NPCPassiveBarrier: NPC-specific passive gate.  VERIFIED that the wrapper
//       specialisations C_CompanionObjectiveGate / C_CompanionModeGate embed a
//       C_NPCPassiveBarrier as their barrier base (RTTI wrapper strings at
//       0x182a88820 / 0x182a89610), i.e. it gates an NPC subtree on companion/
//       objective passive state.
//   [UNVERIFIED] the exact per-tick predicate each Update() evaluates; the
//   gating role is inferred from the decorator shape + the embedding
//   companion-gate wrappers, not from tracing the predicate expression.  The
//   per-tick gate state lives in the per-entity TContext (heap-allocated, NOT
//   in the node object), consistent with the 0x30 stateless-node size.
// ===========================================================================

namespace wh::xgenaimodule::BehaviorTree {

// ---------------------------------------------------------------------------
// Per-entity runtime contexts.  NAMES VERIFIED from the barrier wrapper
// manglings; field layouts [UNVERIFIED].  Heap-allocated per entity, threaded
// as void*, NOT embedded in the node.
//   .?AUS_ExecutionBarrierContext@BehaviorTree@xgenaimodule@wh@@
//   .?AUS_PassiveBarrierContext@BehaviorTree@xgenaimodule@wh@@
//   .?AUS_NPCPassiveBarrierContext@BehaviorTree@xgenaimodule@wh@@
// ---------------------------------------------------------------------------
struct S_ExecutionBarrierContext {
    inline static constexpr auto RTTI = Offsets::RTTI_S_ExecutionBarrierContext;
    uint8_t m_gateOpen = 0;     // [UNVERIFIED]
};

struct S_PassiveBarrierContext {
    inline static constexpr auto RTTI = Offsets::RTTI_S_PassiveBarrierContext;
    uint8_t m_passive = 0;      // [UNVERIFIED]
};

struct S_NPCPassiveBarrierContext {
    inline static constexpr auto RTTI = Offsets::RTTI_S_NPCPassiveBarrierContext;
    uint8_t m_passive = 0;      // [UNVERIFIED]
};

// ---------------------------------------------------------------------------
// C_ExecutionBarrier   (VERIFIED 0x30; primaryVT 0x1821E2E28, debugVT 0x1821E2DF0)
// Base: C_NodeWrapper<C_ExecutionBarrier, C_Decorator, S_ExecutionBarrierContext>
// No own data member - object == sizeof(C_Decorator) == 0x30.
// ---------------------------------------------------------------------------
class C_ExecutionBarrier
    : public C_NodeWrapper<C_ExecutionBarrier, C_Decorator, S_ExecutionBarrierContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_ExecutionBarrier;
    // No additional data members (per-tick gate state lives in the TContext).
};
static_assert(sizeof(C_ExecutionBarrier) == 0x30);

// ---------------------------------------------------------------------------
// C_PassiveBarrier   (VERIFIED 0x30; primaryVT 0x1821E2940, debugVT 0x1821E2908)
// Base: C_NodeWrapper<C_PassiveBarrier, C_ExecutionBarrier, S_PassiveBarrierContext>
// No new data member beyond C_ExecutionBarrier.
// ---------------------------------------------------------------------------
class C_PassiveBarrier
    : public C_NodeWrapper<C_PassiveBarrier, C_ExecutionBarrier, S_PassiveBarrierContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_PassiveBarrier;
    // No additional data members.
};
static_assert(sizeof(C_PassiveBarrier) == 0x30);

// ---------------------------------------------------------------------------
// C_NPCPassiveBarrier   (VERIFIED 0x30; primaryVT 0x18221C008, debugVT 0x18221BFD0)
// Base: C_NodeWrapper<C_NPCPassiveBarrier, C_PassiveBarrier, S_NPCPassiveBarrierContext>
// ctor sub_1806ECEA8 chains sub_18068B250 (Passive) -> sub_18068B2F8 (Exec),
// then installs the NPCPassiveBarrier vtables and copies a variable-reference
// table; it writes NO field at +0x30. Size 0x30 double-confirmed by the derived
// C_CompanionObjectiveGate create thunk sub_1806ECD6C (alloc 0x30 + 0x30
// accounting add).
// ---------------------------------------------------------------------------
class C_NPCPassiveBarrier
    : public C_NodeWrapper<C_NPCPassiveBarrier, C_PassiveBarrier, S_NPCPassiveBarrierContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_NPCPassiveBarrier;
    // No additional data members.
};
static_assert(sizeof(C_NPCPassiveBarrier) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
