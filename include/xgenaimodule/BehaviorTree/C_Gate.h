#pragma once

#include <cstdint>
#include "C_Node.h"
#include "C_Decorator.h"
#include "C_Composite.h"
#include "C_NodeWrapper.h"
#include "C_Composites.h"   // canonical S_SequenceContext/S_SelectorContext/
                            // S_ParallelContext/S_LoopContext + the REAL named
                            // C_Sequence/C_Selector/C_Parallel/C_Loop classes

namespace wh::xgenaimodule::BehaviorTree {

// ---------------------------------------------------------------------------
// Context structs — per-entity runtime data, heap-allocated by NodeCreator.
//
// UNVERIFIED: exact layouts. Sizes and members inferred from BT semantics.
// Need to RE from NodeCreator<>::AllocateRuntimeData and Update methods.
//
// RECONCILIATION (verifier): S_SequenceContext / S_SelectorContext /
// S_ParallelContext / S_LoopContext were ALSO defined here, duplicating (and for
// S_ParallelContext contradicting) the better-evidenced definitions in
// C_Composites.h — an ODR violation when both headers are co-included. They are
// removed here and taken from C_Composites.h via the include above. Only the
// gate/switch/if/fusebox context structs (which have no C_Composites.h home)
// remain below.
// ---------------------------------------------------------------------------

struct S_SwitchContext {
    uint32_t m_activeCase;              // which case/branch is selected
    // UNVERIFIED
};

struct S_GateContext {
    // UNVERIFIED: gate evaluation state
};

// NOTE: S_LoopContext is defined canonically in C_Composites.h (it belongs to
// the IDA-verified named C_Loop class). Removed here to avoid an ODR clash with
// the C_Composites.h include above.

struct S_IfConditionContext {
    // UNVERIFIED: condition evaluation result
};

struct S_IfElseConditionContext {
    bool m_conditionResult;             // which branch to take
    // UNVERIFIED
};

struct S_FuseBoxContext {
    // UNVERIFIED
};

// ---------------------------------------------------------------------------
// Logic classes — stateless policy sketches for C_NodeWrapper.
//
// *** MODEL RECONCILIATION (verifier) ***
// IDA-VERIFIED: the binary has REAL named classes C_Sequence / C_Selector /
// C_Parallel / C_Loop (COLs at vtables 0x1821c1950 / 0x1821efa40 / 0x18219ca20 /
// 0x1821fd758 resolve EXACTLY to ".?AVC_Sequence@...", ".?AVC_Parallel@...",
// ".?AVC_Loop@..." etc.). Those are the genuine node types and are RE-d in
// C_Composites.h (Sequence/Selector/Parallel == 0x40, Loop == 0x30; there is NO
// cached child-count member - that "@+0x40" field was a fabrication, corrected).
// The C_SequenceLogic / C_SelectorLogic / C_ParallelLogic / C_LoopLogic "policy"
// classes below and the corresponding *Node typedefs were an INVENTED alternative
// model: NO "C_*Logic" RTTI name exists in the binary for these four. They are
// retained ONLY as a documentation sketch and MUST NOT be treated as real types —
// use C_Composites.h's C_Sequence/C_Selector/C_Parallel/C_Loop instead. The
// Switch / If / IfElse / FuseBox entries are likewise [UNVERIFIED] sketches (no
// COL resolved for them this pass).
// ---------------------------------------------------------------------------

class C_SequenceLogic {};   // SUPERSEDED by C_Composites.h::C_Sequence (VERIFIED)
class C_SelectorLogic {};   // SUPERSEDED by C_Composites.h::C_Selector (VERIFIED)
class C_ParallelLogic {};   // SUPERSEDED by C_Composites.h::C_Parallel (VERIFIED)
class C_LoopLogic {};       // SUPERSEDED by C_Composites.h::C_Loop     (VERIFIED)
class C_SwitchLogic {};            // [UNVERIFIED] no COL resolved
class C_IfConditionLogic {};       // [UNVERIFIED]
class C_IfElseConditionLogic {};   // [UNVERIFIED]
class C_FuseBoxLogic {};           // [UNVERIFIED]

// ---------------------------------------------------------------------------
// C_Gate — wrapper-based conditional gate node: a 2-child fixed composite whose
//          "Then" / "Else" branches are selected by a bound condition.
//
// RTTI: .?AVC_Gate@BehaviorTree@xgenaimodule@wh@@   (primary vtable 0x1821a0338)
// Size: 0x68 bytes (VERIFIED)
// Base: C_NodeWrapper<C_Gate, C_FixedComposite<2>, S_GateContext>  (VERIFIED)
//
// SIZE / LAYOUT evidence (2026-05):
//   * complete-object deleting dtor sub_1801FE1E8 -> operator delete(this, 0x68);
//     the node ctor is sub_1801FE394.  (A base-subobject deleting dtor
//     sub_181447648 frees only 0x58 - that is NOT the complete size; ignore it.)
//   * derived C_LuaGate (ctor sub_1801FE578) appends its lua block at +0x68 and
//     frees 0x78, so the C_Gate region ends exactly at 0x68.
//   * C_FixedComposite<2> base == 0x38 (0x28 C_Node + 2 inline child ptrs); the
//     gate therefore adds 0x30 of own state at +0x38..+0x68.
//
// OWN-MEMBER LAYOUT (+0x38..+0x68), from ctor sub_1801FE394 -> sub_1801FE454 /
// sub_1801FE418 / sub_1801FE43C:
//   +0x28,+0x30  the two C_FixedComposite<2> child node pointers (inherited)
//   +0x38        "Then" bound-variable reference (branch-0 condition source)
//   +0x40        "Else" bound-variable reference (branch-1 condition source)
//   +0x48,+0x50  pointers initialised to &(+0x58) / &(+0x60)  (a small index)
//   +0x58,+0x60  cached copies of the child pointers at +0x28 / +0x30
//   The exact field TYPES of the +0x38..+0x68 block are [UNVERIFIED]; it is
//   modelled as a raw byte block so sizeof is pinned to the verified 0x68.
// ---------------------------------------------------------------------------
class C_Gate : public C_NodeWrapper<C_Gate, C_FixedComposite<2>, S_GateContext> {
public:
    const char* GetNodeCategory() const override { return "Gate"; } // [6]

    // Own state beyond the C_FixedComposite<2> base (0x30 bytes: "Then"/"Else"
    // condition refs + a child-pointer link block).  Field types [UNVERIFIED];
    // kept as a raw block to fix the verified 0x68 object size.
    uint8_t m_gateState[0x30];                   // +0x38 .. +0x68
};
static_assert(sizeof(C_Gate) == 0x68);

// ---------------------------------------------------------------------------
// Sketch typedefs (NON-canonical).
//   Seq/Sel/Par/Loop are REMOVED here: the canonical, IDA-verified node types are
//   C_Composites.h::{C_Sequence, C_Selector, C_Parallel, C_Loop}. Use those.
//   The four below remain [UNVERIFIED] sketches (no COL resolved this pass).
// ---------------------------------------------------------------------------
using SwitchNode        = C_NodeWrapper<C_SwitchLogic,          C_SwitchBase,        S_SwitchContext>;          // [UNVERIFIED]
using IfConditionNode   = C_NodeWrapper<C_IfConditionLogic,     C_Decorator,         S_IfConditionContext>;     // [UNVERIFIED]
using IfElseNode        = C_NodeWrapper<C_IfElseConditionLogic, C_Decorator,         S_IfElseConditionContext>; // [UNVERIFIED] (was wrongly S_IfConditionContext)
using FuseBoxNode       = C_NodeWrapper<C_FuseBoxLogic,         C_FixedComposite<3>, S_FuseBoxContext>;          // [UNVERIFIED]

}  // namespace wh::xgenaimodule::BehaviorTree
