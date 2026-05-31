#pragma once
// =============================================================================
// wh::xgenaimodule::BehaviorTree::C_AddBuff
//
// Behaviour-tree leaf for the XML element <AddBuff .../> (buff-application family;
// used by the poison / generic buff systems).
//
// MODULE : xgenaimodule (CryEngine3 + Warhorse AI), retail WHGame.dll
//          (imagebase 0x180000000).
// Naming convention: wh::xgenaimodule::BehaviorTree::C_AddBuff::<fn>_<addr>
//
// SCOPE OF THIS HEADER (read this first):
//   The structural facts (RTTI/COL chain, vtable addresses, the node OBJECT
//   layout from the ctor, and the S_AddBuffContext layout from its copy-ctor) are
//   VERIFIED and load-bearing.
//   The per-slot BEHAVIOUR and the engine call-chain that ultimately applies the
//   buff are NOT yet established and are explicitly marked [UNVERIFIED]/[OPEN].
//   An earlier draft asserted a specific buff-apply chain (via C_BuffManager, and
//   later via "C_Soul::AddBuff_1805F0D3C"); BOTH were wrong (name-matches /
//   misread decompiles) and have been removed. They are recorded under
//   [REFUTED] so they are not reintroduced. This file deliberately contains no
//   guessed call chain.
//
// -----------------------------------------------------------------------------
// CONCRETE INSTANTIATION (VERIFIED via RTTI COL chain; mdisp = sub-object offset)
//   node     C_NodeWrapper<C_AddBuff, C_Node, S_AddBuffContext>
//              primary  vtable 0x182211490  (COL 0x18244d7c0, mdisp 0)
//              I_DebugNode  vt 0x182211458  (COL 0x18244d7e8, mdisp 8)
//              ctor 0x1806E38B0
//   policy   C_AddBuff               vtable 0x182211220 / 0x1822111e8 (mdisp 0/8)
//   context  S_AddBuffContext        vtable 0x1821fb3a8 ; copy-ctor 0x1806C7580
//   factory  C_NodeFactory_AddBuff   vtable 0x18238adf0  (RTTI str 0x182b093e0)
//            C_NodeFactoryImpl<...>  vtable 0x18238ada8  (RTTI str 0x182b09310)
//   ctxPool  C_NodeContextPool<S_AddBuffContext,...>  vtable 0x182385250
//   RTTI strings VERIFIED (get_string): policy 0x182b098e0, wrapper 0x182b09850,
//   context 0x182b09920, named-factory 0x182b093e0.
//
// -----------------------------------------------------------------------------
// NODE OBJECT LAYOUT — VERIFIED EXACT from ctor sub_1806E38B0:
//   +0x00 I_Node vptr      (= C_NodeWrapper<C_AddBuff,...>::vftable, 0x182211490)
//   +0x08 I_DebugNode vptr (= ...::vftable, 0x182211458)
//   +0x10 void*    m_pNodeData = 0
//   +0x18 uint32_t m_nodeId    = *(src+0x18)   (+0x1C pad)
//   +0x20 void*    m_pCreator  = 0
//   => no per-tick state on the node; object size == sizeof(C_Node) == 0x28.
//
// -----------------------------------------------------------------------------
// C_AddBuff-SPECIFIC VTABLE SLOTS — found WITHOUT positional guessing by diffing
//   node vtable 0x182211490 against another C_Node-leaf node vtable
//   (C_GetItemType 0x1822039b8): 55/60 slots are byte-identical shared machinery;
//   exactly these 5 differ and are therefore C_AddBuff's own overrides. The
//   ADDRESSES are VERIFIED; the interface-method identity of each shuffled slot is
//   NOT asserted. Behaviour notes are only as strong as the cited decompile:
//     [ 0] 0x180705660  ` return &unk_183799718; `  (returns a static blob ptr;
//                        role [UNVERIFIED] — likely a type/category descriptor.)
//     [ 5] 0x1806E37D4  pool-allocates a 0x28 object then sub_1806E384C(obj,this)
//                        (a Clone/Create-style slot; [UNVERIFIED] exact contract.)
//     [14] 0x181568ED8  iterates three bound-variable tables and StringHashes each
//                        present var into this node's context — the leaf's
//                        bound-variable BIND step. (VERIFIED behaviour.)
//     [15] 0x181571AC8  bound-variable counterpart. [UNVERIFIED detail]
//     [40] 0x181559FF4  iterates an S_SilentVariableReference set and builds
//                        std::function<C_Variable*(C_Variable*,bool&)> bindings
//                        (more variable-reference plumbing). (VERIFIED behaviour;
//                        does NOT itself contain a buff-apply call.)
//
// -----------------------------------------------------------------------------
// [OPEN] WHERE THE BUFF IS ACTUALLY APPLIED — NOT YET FOUND.
//   None of the 5 type-specific slots above contains the buff-application call;
//   they are all variable-binding/allocation machinery. The actual effect is
//   reached at tick time through one of the SHARED slots dispatching to a
//   policy-provided callback that these slots install (the std::function built in
//   slot 40 is the lead). Tracing that dispatch to the concrete buff API is the
//   remaining work for this node and is intentionally left unstated here rather
//   than guessed.
//
// [REFUTED] earlier-draft claims, kept so they are not reintroduced:
//   * "C_AddBuff -> C_BuffManager::AddBuff_18056998C": name-match only;
//     AddBuff_18056998C's only callers are sub_180569938 / sub_1811CA8AC (not this
//     node), and no slot of vt 0x182211490 reaches it within 2 call levels.
//   * "C_Soul::AddBuff_1805F0D3C" and the soul-lookup chain via "sub_181565330":
//     sub_181565330 is NOT a function; 0x1805F0D3C is a std::_Ref_count ctor for a
//     combat clip, not a soul buff. Both were misreads and are discarded.
// =============================================================================

#include "C_Node.h"          // C_Node (0x28 leaf base) + I_Node / I_DebugNode + E_NodeStatus
#include "C_NodeWrapper.h"   // C_NodeWrapper<TNode, TBase, TContext>
#include "C_NodeContext.h"   // S_BaseNodeContext, C_NodeContextPool, casting policy
#include "C_NodeFactory.h"   // I_NodeFactory, C_NodeFactoryImpl<TNode, TCasting>
#include <cstdint>

namespace wh::xgenaimodule::BehaviorTree {

// -----------------------------------------------------------------------------
// S_AddBuffContext — per-(tree-instance) runtime data for the AddBuff leaf.
//   Owned one-per-instance by C_NodeContextPool<S_AddBuffContext,...> (vt
//   0x182385250); passed to the policy methods as the opaque runtimeData.
//
//   Layout VERIFIED from copy-ctor sub_1806C7580(dst,src):
//     +0x00 vptr      -> S_AddBuffContext::vftable (0x1821fb3a8). The ctor writes
//                        S_BaseNodeContext::vftable first, then the derived one
//                        => S_AddBuffContext IS polymorphic and derives S_BaseNodeContext.
//     +0x08 m_status  -> 1-byte BT status (copied from src+0x08).
//     +0x10 m_unk10   -> uint64 copied verbatim (role [UNVERIFIED]).
//     +0x18 m_subA    -> sub-object copied by sub_1803AB664 (spans +0x18..+0x27).
//     +0x28 m_subB    -> tail sub-object copied by sub_1803ACA08.
//   m_subA/m_subB hold the leaf's bound-variable state filled by slot 14. Their
//   element types are [UNVERIFIED] (copy helpers not yet decompiled); the offsets
//   and copy boundaries ARE verified from the ctor. Total sizeof is [UNVERIFIED]
//   (at least 0x38; the pool element stride was not measured this pass).
// -----------------------------------------------------------------------------
struct S_AddBuffContext : public S_BaseNodeContext   // base supplies the +0x00 vptr
{
    /* +0x08 */ uint8_t   m_status;            // BT E_NodeStatus byte
    /* +0x09 */ uint8_t   _pad09[7];
    /* +0x10 */ uint64_t  m_unk10;             // copied by ctor; role [UNVERIFIED]
    /* +0x18 */ uint8_t   m_subA[0x10];        // sub_1803AB664-copied [UNVERIFIED type]
    /* +0x28 */ uint8_t   m_subB[0x10];        // sub_1803ACA08-copied [UNVERIFIED type/size]
};

// -----------------------------------------------------------------------------
// C_AddBuff — stateless behaviour policy plugged into the wrapper. Modelled as
//   deriving C_Node so the vtable/inheritance chain is explicit; the wrapper
//   installs the C_Node-based node vtable (ctor sub_1806E38B0). Adds no data
//   members: sizeof(node) == sizeof(C_Node) == 0x28.
//
//   No member functions are declared here on purpose: the 5 type-specific slot
//   ADDRESSES are documented in the banner, but their interface-method identity
//   is unproven (interfuscator slot shuffle) and the buff-apply path is [OPEN].
//   Declaring named methods would imply a slot->name mapping that is not verified.
// -----------------------------------------------------------------------------
class C_AddBuff : public C_Node
{
public:
    using RuntimeData = S_AddBuffContext;
    // Type-specific vtable slots (addresses VERIFIED; see banner for behaviour):
    //   slot 0  = 0x180705660   slot 5  = 0x1806E37D4   slot 14 = 0x181568ED8
    //   slot 15 = 0x181571AC8   slot 40 = 0x181559FF4
};
static_assert(sizeof(C_AddBuff) == 0x28);   // VERIFIED EXACT from ctor sub_1806E38B0

// Concrete node type as instantiated in the binary (object size 0x28).
using C_AddBuffNode =
    C_NodeWrapper<C_AddBuff, C_Node, S_AddBuffContext>;        // vt 0x182211490, ctor 0x1806E38B0

// Per-type factory singleton.
using C_NodeFactory_AddBuff =
    C_NodeFactoryImpl<C_AddBuff, C_DefaultNodeContextCasting<S_AddBuffContext> >; // vt 0x18238ada8

// -----------------------------------------------------------------------------
// XML attributes — name-strings VERIFIED present in WHGame.dll:
//   "SoulWUID" @ 0x182358b00 , "BuffGUID" @ 0x1827010e0.
// Consumed as bound blackboard variables gathered by slot 14 into
// S_AddBuffContext (NOT stored as literal NodeAttribute<T> values on the node).
// The exact backing NodeAttribute specialisation, if any, is [UNVERIFIED].
// -----------------------------------------------------------------------------

} // namespace wh::xgenaimodule::BehaviorTree
