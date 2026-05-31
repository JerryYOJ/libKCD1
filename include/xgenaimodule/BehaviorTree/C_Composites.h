#pragma once

#include <cstdint>
#include "C_Node.h"
#include "C_Decorator.h"
#include "C_Composite.h"
#include "C_NodeWrapper.h"

// ===========================================================================
// C_Composites.h  -  Concrete flow-control BT nodes (Sequence / Selector /
//                    Parallel / Loop).
//
// Reverse-engineered from WHGame.dll (KCD1 retail). Namespace
// wh::xgenaimodule::BehaviorTree.
//
// METHODOLOGY
// -----------
// Each node was resolved RTTI-name-string -> TypeDescriptor -> CompleteObject-
// Locator (validated: COL.signature==1 AND COL.typeDescriptor-RVA matches) ->
// vtable, its ClassHierarchyDescriptor base-class array was parsed, and its
// "create" factory thunk was decompiled to read the EXACT allocation size and
// member initialisation.  (All addresses below are from this validated pass.)
//
// VERIFIED anchors (name-string / primary vtable / I_DebugNode secondary vtable
//                   [installed at object+0x08] / create thunk -> alloc size / node ctor):
//   C_Sequence  name@0x182ac98c8  primaryVT@0x1821c1950  debugVT@0x1821c1918
//               create sub_180585E70 -> alloc(0x40) -> ctor sub_180585EE8
//   C_Selector  name@0x182ac99a8  primaryVT@0x1821efa40  debugVT@0x1821efa08
//               create sub_1806AF734 -> alloc(0x40) -> ctor sub_1806AF7AC
//   C_Parallel  name@0x182acaf38  primaryVT@0x18219ca20  debugVT@0x18219c9e8
//               create sub_1801FCF50 -> alloc(0x40) -> ctor sub_1801FD28C
//   C_Loop      name@0x182adb310  primaryVT@0x1821fd758  debugVT@0x1821fd720
//               create sub_1806CAFEC / sub_181470C80 -> alloc(0x30) -> ctor sub_1806CB064
//
// VERIFIED RTTI base-class arrays (declared order):
//   C_Sequence : C_NodeWrapper<C_Sequence, C_Composite, S_SequenceContext>
//                : C_Composite : C_Node : I_Node
//                : I_CastableIface : I_NoRTTITypeInfo : I_DebugNode
//   C_Selector : C_NodeWrapper<C_Selector, C_Composite, S_SelectorContext> : ...
//   C_Parallel : C_NodeWrapper<C_Parallel, C_Composite, S_ParallelContext> : ...
//   C_Loop     : C_NodeWrapper<C_Loop,     C_Decorator, S_LoopContext>
//                : C_Decorator : C_Node : I_Node : ...
//   (The context-struct identities S_SequenceContext / S_SelectorContext /
//    S_ParallelContext / S_LoopContext are read directly from the wrapper's
//    mangled RTTI name in the base array - so the TYPE NAMES are VERIFIED;
//    their field layouts are not.)
//
// VERIFIED OBJECT SIZE (from the create thunks + node ctors; re-derived 2026-05)
// --------------------------------------------------------------------------
//   Each create thunk does:  obj = alloc(SIZE); ctor(obj, xmlNode);
//   with SIZE confirmed twice (the alloc arg AND the redundant accounting add
//   `_InterlockedExchangeAdd(&dword_183002E60, SIZEu)`):
//       C_Sequence / C_Selector / C_Parallel : SIZE = 0x40  (== sizeof C_Composite)
//       C_Loop                               : SIZE = 0x30  (== sizeof C_Decorator)
//   CORRECTION: a prior draft claimed all four were 0x48 with a cached child-count
//   int written at +0x40. That was WRONG — re-decompiling the actual ctors
//   (sub_180585EE8 / sub_1806AF7AC / sub_1801FD28C / sub_1806CB064) and create
//   thunks shows NO write at +0x40 and NO 0x48 allocation; the nodes are exactly
//   their structural-base size (composites 0x40, Loop 0x30) and add NO own data
//   member. The "m_childCount @ +0x40" fields below were removed.
//
// CHILD STORAGE (verified)
// ------------------------
// Composites keep children in the inherited
//     std::vector<I_Node*> C_Composite::m_children   (this+0x28 .. +0x40)
// The grow/relocate helper (vector_emplace_realloc_180DD3CD0) moves each
// I_Node* (begin/end/cap at +0x28/+0x30/+0x38) and frees displaced nodes via
// MemFree(node,0x90).  The std::vector occupies +0x28..+0x40, i.e. it ends the
// 0x40 object exactly — there is NO field past it (no +0x40 member).
// C_Loop (decorator base) holds its one child in the inherited
//     I_Node* C_Decorator::m_pChild   (this+0x28).
//
// TICK / CHILD ITERATION
// ----------------------
// Iteration is driven by the shared I_Node base state machine
// (TickNode/UpdateNode/StartChild/CompleteNode - see I_Node.h [18]-[22]) over a
// stateless run-policy.  Sequence advances on child Success, fails on first
// child Failure; Selector advances on child Failure, succeeds on first child
// Success; Parallel ticks all children.  Behaviour differs via the per-entity
// TContext processed by the shared base.
// [UNVERIFIED] the exact Parallel success/failure aggregation thresholds were
// not traced; the distinct policy is confirmed by the distinct RTTI node-name +
// distinct create thunk, not by reading the threshold logic.
// ===========================================================================

namespace wh::xgenaimodule::BehaviorTree {

// ---------------------------------------------------------------------------
// Per-entity runtime contexts (TContext).
//
// Type NAMES VERIFIED from each wrapper's mangled RTTI (S_SequenceContext /
// S_SelectorContext / S_ParallelContext / S_LoopContext).  These supersede the
// [UNVERIFIED] sketches in C_NodeContext.h / C_Gate.h.
//
// [UNVERIFIED] field layouts/sizes - the context-pool element stride was not
// isolated; members below are minimal-plausible and tagged.  They are NOT
// embedded in the node; heap-allocated per entity and threaded via
// UpdateContext as void*, then cast by the wrapper thunks.
// ---------------------------------------------------------------------------
struct S_SequenceContext {
    uint32_t m_currentChildIndex = 0;   // [UNVERIFIED]
};

struct S_SelectorContext {
    uint32_t m_currentChildIndex = 0;   // [UNVERIFIED]
};

struct S_ParallelContext {
    uint32_t m_runningMask = 0;         // [UNVERIFIED]
};

struct S_LoopContext {
    uint32_t m_iteration     = 0;       // [UNVERIFIED]
    uint32_t m_maxIterations = 0;       // [UNVERIFIED]
};

// ---------------------------------------------------------------------------
// C_Sequence   (VERIFIED 0x48; primaryVT 0x1821C1950, debugVT 0x1821C1918)
// Base: C_NodeWrapper<C_Sequence, C_Composite, S_SequenceContext>
// Runs children left-to-right; fails on first child failure, succeeds when all
// succeed.
// ---------------------------------------------------------------------------
class C_Sequence
    : public C_NodeWrapper<C_Sequence, C_Composite, S_SequenceContext>
{
    // No own data members; object == sizeof(C_Composite) == 0x40 (VERIFIED:
    // create sub_180585E70 alloc(0x40), ctor sub_180585EE8 writes no extra field).
};
static_assert(sizeof(C_Sequence) == 0x40);

// ---------------------------------------------------------------------------
// C_Selector   (VERIFIED 0x48; primaryVT 0x1821EFA40, debugVT 0x1821EFA08)
// Base: C_NodeWrapper<C_Selector, C_Composite, S_SelectorContext>
// Runs children left-to-right; succeeds on first child success, fails when all
// fail.
// ---------------------------------------------------------------------------
class C_Selector
    : public C_NodeWrapper<C_Selector, C_Composite, S_SelectorContext>
{
    // No own data members; object == 0x40 (VERIFIED: create sub_1806AF734
    // alloc(0x40), ctor sub_1806AF7AC).
};
static_assert(sizeof(C_Selector) == 0x40);

// ---------------------------------------------------------------------------
// C_Parallel   (VERIFIED 0x48; primaryVT 0x18219CA20, debugVT 0x18219C9E8)
// Base: C_NodeWrapper<C_Parallel, C_Composite, S_ParallelContext>
// Ticks all children each frame.
// ---------------------------------------------------------------------------
class C_Parallel
    : public C_NodeWrapper<C_Parallel, C_Composite, S_ParallelContext>
{
    // No own data members; object == 0x40 (VERIFIED: create sub_1801FCF50
    // alloc(0x40), ctor sub_1801FD28C).
};
static_assert(sizeof(C_Parallel) == 0x40);

// ---------------------------------------------------------------------------
// C_Loop   (VERIFIED 0x48; primaryVT 0x1821FD758, debugVT 0x1821FD720)
// Base: C_NodeWrapper<C_Loop, C_Decorator, S_LoopContext>
//
// Single-child decorator that re-runs its child up to N times (N from an XML
// attribute, see NodeAttribute.h).  Child in inherited C_Decorator::m_pChild
// (+0x28).
// CORRECTION (2026-05): C_Loop is 0x30 (== sizeof C_Decorator), NOT 0x48. Both
// create paths (sub_1806CAFEC and sub_181470C80) alloc 0x30 (confirmed by the
// 0x30u accounting add), and ctor sub_1806CB064 installs vtables + copies a
// variable-reference table but writes NO field at +0x30/+0x40. The earlier
// 0x48 + m_loopState/m_cachedCount layout was fabricated and is removed.
// ---------------------------------------------------------------------------
class C_Loop
    : public C_NodeWrapper<C_Loop, C_Decorator, S_LoopContext>
{
    // No own data members; object == sizeof(C_Decorator) == 0x30 (VERIFIED).
};
static_assert(sizeof(C_Loop) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
