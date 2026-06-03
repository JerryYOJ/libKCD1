#pragma once

#include <cstdint>
#include "../I_Node.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"
#include "../C_NodeFactory.h"

// ===========================================================================
// C_StopFastTravel - behavior-tree leaf ACTION node (fast-travel system).
//
//   Module:    xgenaimodule  (AI / behavior-tree)
//   Namespace: wh::xgenaimodule::BehaviorTree
//   XML tag:   "StopFastTravel"   (name string @ 0x1822e8610)
//   Subsystem: "Player"           (registration tag - see factory below)
//
// ---------------------------------------------------------------------------
// RTTI evidence (all name strings verified present in .rdata):
//   0x182ab01e0  .?AVC_StopFastTravel@BehaviorTree@xgenaimodule@wh@@
//   0x182ab0230  .?AV?$C_NodeWrapper@VC_StopFastTravel@...@VC_Node@234@US_StopFastTravelContext@234@@...
//   0x182ab03b0  .?AUS_StopFastTravelContext@BehaviorTree@xgenaimodule@wh@@
//   0x182ab00b0  .?AVC_NodeFactory_StopFastTravel@BehaviorTree@xgenaimodule@wh@@
//   0x182ab0100  .?AV?$C_NodeFactoryImpl@VC_StopFastTravel@...@V?$C_DefaultNodeContextCasting@US_StopFastTravelContext@...@@@...
//   0x182ab1110  .?AV?$C_NodeContextPool@US_StopFastTravelContext@...@V?$C_DefaultNodeContextCasting@...@@@...
//
// RTTI resolution (signature-validated COLs; td = name_addr - 0x10; a COL is
// accepted only when COL+0x00 sig==1 AND COL+0x0C td-RVA == node td):
//   node    td=0x182ab01d0
//       COL 0x18252f114 -> PRIMARY  vtable (I_Node, 60 slots) @ 0x18233d710
//       COL 0x18252f13c -> SECONDARY vtable (I_DebugNode, node+0x08) @ 0x18233d948
//   context td=0x182ab03a0  -> context vtable @ 0x18233d6c0
//   factory td=0x182ab00a0  COL 0x18252f0d0 -> factory vtable @ 0x18233dcc0
//
// The CONCRETE node type instantiated at runtime is:
//     C_NodeWrapper< C_StopFastTravel, C_Node, S_StopFastTravelContext >
// i.e. C_StopFastTravel is a stateless behavior *policy* whose lifecycle
// methods are inlined into the wrapper's vtable (see C_NodeWrapper.h).
// Structural base = C_Node (leaf, no children, 0x28 bytes).
//
// ---------------------------------------------------------------------------
// NODE CTOR (VERIFIED) - sub_181889630, called by CreateNode:
//     *(void**)(this+0x00) = 0x18233D710;   // primary vtable   (I_Node, 60 slots)
//     *(void**)(this+0x08) = 0x18233D948;   // secondary vtable (I_DebugNode)
//     sub_18139D000(this);                   // base init: m_pNodeData=0 (+0x10),
//                                            //            m_pCreator=0  (+0x20)
//   => object layout is EXACTLY C_Node (0x28). The wrapper adds no data members.
//
// ---------------------------------------------------------------------------
// PRIMARY VTABLE @ 0x18233d710 (60 slots, read & each thunk resolved).
// Indexed against I_Node.h. The leaf shape matches C_Node exactly:
//   slots [47][48][49][50][51][52][54][55][57][58] = _guard_check_icall_nop
//                                                    (leaf has no children).
// The single node-specific lifecycle override is:
//   slot[14] OnInitialize = 0x1813b6c44  (sub_1813B6C44)   <-- node behavior
//   slot[15] OnTerminate  = 0x1803aea68  (shared engine stub; reads child state)
//   slot[17] Update       = 0x1803add80  (shared engine stub; clears flag, ticks)
//   slot[16] GetChildStatus = 0x181546330
//   slot[39] Tick         = 0x18139aa14  (shared leaf tick driver)
// Update/OnTerminate are the SHARED stubs used by many simple leaf nodes, so the
// node-specific work is performed in OnInitialize (fired once on activation).
//
// ---------------------------------------------------------------------------
// BEHAVIOR (VERIFIED structure of OnInitialize sub_1813B6C44; a1 = context):
//   It is a "snapshot named variables into the context" handler, structurally
//   identical to C_Expression::OnInitialize. It iterates THREE static
//   S_VariableReference attribute tables and, for each entry, reads a field at
//   (context + table_entry.offset), StringHash-processes it (sub_1813A2C54),
//   and writes the result through an engine vfunc at object +0x218:
//     table A @ xmmword_1836F2BF0  (stride 0x10; field source = context + off)
//     table B @ xmmword_1836F2C08  (stride 0x04; source via sub_180659964(ctx)+off,
//                                   read through that object's vtable +0x10)
//     table C @ xmmword_1836F2C20  (stride 0x04; source = sub_180659964(ctx)+off)
//   sub_1813A2C54(index, tableId) yields the hashed key; sub_181678A90 finalizes
//   the value; vfunc +0x218 commits it. Returns 1.
//   => StopFastTravel binds/stages a fixed set of S_VariableReference entries
//      (declared in those three global tables) from the per-entity context into
//      the AI knowledge/variable system when the node activates.
//   The "Player" registration subsystem (below) routes this to the player brain.
//   See [UNVERIFIED] for the exact variable names and what each table holds.
//
// ---------------------------------------------------------------------------
// XML -> C++ -> engine call chain:
//   <StopFastTravel/>   (no per-node tuning attributes - see factory)
//      registration / setup  (factory vtable slot[2] = sub_1813A73EC):
//          StringHash("StopFastTravel") x2 + StringHash("Player");
//          sub_1812ECC90(factory, nameHash, /*flag*/1, "Player"Hash, &nameHash)
//          -> registers BT tag "StopFastTravel" under subsystem "Player".
//      -> node object built by sub_181889630 (0x28 == sizeof(C_Node)).
//      -> per-entity S_StopFastTravelContext acquired from the context pool;
//         context vtable 0x18233d6c0 installed; the factory's variable-reference
//         accessors (slots [3]/[5] = sub_18139CF6C / sub_18139D01C) install
//         wh::xgenaimodule::S_VariableReference::vftable entries.
//      -> on activate (slot 14 OnInitialize): stage the three S_VariableReference
//         tables from the context into the AI variable system (vfunc +0x218).
//      -> Update / OnTerminate are shared engine stubs; the leaf completes.
// ===========================================================================

namespace wh::xgenaimodule::BehaviorTree {

// ---------------------------------------------------------------------------
// S_StopFastTravelContext - per-entity runtime data for one StopFastTravel node.
//
// Derives from S_BaseNodeContext (defined in C_NodeContext.h).
// Context vtable @ 0x18233d6c0; per-entity ctor at sub_181395532 / sub_18139555B.
//
// OnInitialize reads fields out of this context at byte offsets supplied by the
// three static S_VariableReference tables (see banner). The set of fields and
// the exact total size are governed by those tables (NOT a single fixed member
// list), so concrete members below are intentionally minimal and the layout tail
// is flagged. The base sub-layout is inherited from S_BaseNodeContext.
// ---------------------------------------------------------------------------
struct S_StopFastTravelContext : public S_BaseNodeContext {
    // S_BaseNodeContext provides +0x00 vtable and +0x08..+0x20.
    // Node-specific S_VariableReference slots follow; their offsets are encoded
    // in the global tables (xmmword_1836F2BF0 / _C08 / _C20) rather than read as
    // named members here. [layout tail UNVERIFIED]
};

// ---------------------------------------------------------------------------
// C_StopFastTravel - stateless behavior policy (the TNode of the wrapper).
//
// Has NO data members (does not appear in the wrapper's RTTI base list). The
// wrapper inlines its OnInitialize into primary-vtable slot 14; Update (slot 17)
// and OnTerminate (slot 15) resolve to shared engine stubs.
//
// wh::xgenaimodule::BehaviorTree::C_StopFastTravel::OnInitialize_0x1813B6C44
// ---------------------------------------------------------------------------
class C_StopFastTravel {
public:
    // Fire-once on activation: stage the three static S_VariableReference tables
    // from the per-entity context into the AI variable system (commit via the
    // engine vfunc at object +0x218). Returns success.
    void OnInitialize(S_StopFastTravelContext& ctx) const;   // slot 14, sub_1813B6C44

    // Shared engine stub (slot 17, sub_1803ADD80): clears a per-node flag and
    // advances the leaf; not StopFastTravel-specific.
    E_NodeStatus Update(S_StopFastTravelContext& ctx) const;

    // Shared engine stub (slot 15, sub_1803AEA68): reads child/leaf state.
    void OnTerminate(S_StopFastTravelContext& ctx) const;
};
static_assert(sizeof(C_StopFastTravel) == 1,
              "C_StopFastTravel is a stateless policy (no data members)");

// ---------------------------------------------------------------------------
// C_StopFastTravelNode - the concrete BT node type registered for "StopFastTravel".
// This IS the object the factory allocates (0x28 bytes == sizeof(C_Node)).
//   primary vtable   0x18233d710   (I_Node, 60 slots)
//   secondary vtable 0x18233d948   (I_DebugNode, at node+0x08)
// ---------------------------------------------------------------------------
using C_StopFastTravelNode =
    C_NodeWrapper<C_StopFastTravel, C_Node, S_StopFastTravelContext>;
static_assert(sizeof(C_StopFastTravelNode) == 0x28,
              "wrapper adds no data members over C_Node; node object is 0x28");

// ---------------------------------------------------------------------------
// C_NodeFactory_StopFastTravel - factory for XML tag "StopFastTravel".
//   RTTI:    .?AVC_NodeFactory_StopFastTravel@BehaviorTree@xgenaimodule@wh@@
//   vtable:  0x18233dcc0   (signature-validated COL 0x18252f0d0)
//   slot[0] GetContextSize       sub_18139CEB8  (returns a size from a static
//                                  S_VariableReference table; not a fixed literal)
//   slot[2] CreateNode / setup   sub_1813A73EC  (StringHash "StopFastTravel" +
//                                  "Player"; registers the tag via sub_1812ECC90)
//   slot[3] VarRefAccessor       sub_18139CF6C  (installs S_VariableReference vtable)
//   slot[5] VarRefAccessor       sub_18139D01C  (installs S_VariableReference vtable)
//   slot[6]                      sub_18139CDE8
//
// VERIFIED: C_StopFastTravel declares NO scalar XML tuning attributes; its
// inputs are S_VariableReference bindings driven by the three global tables, not
// NodeAttribute<T> entries.
//
// Equivalent to:
//   C_NodeFactoryImpl< C_StopFastTravel,
//                      C_DefaultNodeContextCasting<S_StopFastTravelContext> >.
// ---------------------------------------------------------------------------
// CORRECTED (verifier): the 2nd template arg is the casting policy, NOT the
// context struct itself. Was C_NodeFactoryImpl<C_StopFastTravel,
// S_StopFastTravelContext> (passed the context where TCasting belongs).
using C_NodeFactory_StopFastTravel =
    C_NodeFactoryImpl< C_StopFastTravel,
                       C_DefaultNodeContextCasting<S_StopFastTravelContext> >;

}  // namespace wh::xgenaimodule::BehaviorTree

// ===========================================================================
// [UNVERIFIED] - items not fully nailed down by analysis:
//
//  * The exact variable names / contents of the three S_VariableReference tables
//    (xmmword_1836F2BF0 stride 0x10, xmmword_1836F2C08 stride 4, xmmword_1836F2C20
//    stride 4) that OnInitialize stages. The ITERATION structure and the commit
//    vfunc (+0x218) are VERIFIED by decompiling sub_1813B6C44; the per-entry
//    semantics (which knowledge variable each maps to, e.g. a fast-travel flag)
//    were NOT resolved. This is the same "snapshot $vars" mechanism as
//    C_Expression - reconcile against C_Expression.h for the table-entry format.
//
//  * Whether StopFastTravel ultimately reaches wh::playermodule::C_FastTravel.
//    NOT established. The node operates through the AI variable system under the
//    "Player" subsystem, not via a direct C_FastTravel call. The task hint to
//    cross-ref C_FastTravel skip-time did NOT match the observed code path.
//
//  * Exact size and full member layout of S_StopFastTravelContext. The context
//    vtable (0x18233d6c0) and ctor (sub_181395532) are identified, but the field
//    set is table-driven (offsets live in the global tables), so a fixed member
//    list and total sizeof are NOT asserted here. (An earlier draft's "0x40" was
//    read from the WRONG factory vtable and is retracted.)
//
//  * S_BaseNodeContext sub-layout (+0x08..+0x20) is reused from C_NodeContext.h,
//    inferred from the shared base rather than read from this type's ctor.
//
//  * Precise E_NodeStatus values returned by the shared Update/OnTerminate stubs
//    (sub_1803ADD80 / sub_1803AEA68) per tick - these are generic leaf helpers;
//    the success status is produced by the leaf tick driver (slot 39, sub_18139AA14).
//
//  RETRACTED (from earlier in-session drafts, do NOT trust): node vtable
//  0x182ab0220 / 0x1825300f8; methods 0x181802bb0 / 0x181802db8 / 0x181802d90;
//  a C_FastTravel controller +0xC8/+0xD0 pairing; context size 0x40; and the
//  "invalidate var id 0x270F4" behavior (that came from sub_1801FCF50, a generic
//  allocator, and sub_1801F4DB0, an atexit thunk - both unrelated to this node).
//  The verified data is: primary vtable 0x18233d710, OnInitialize sub_1813B6C44,
//  factory vtable 0x18233dcc0, registration sub_1813A73EC ("StopFastTravel"/"Player").
// ===========================================================================
