#pragma once

#include <cstdint>
#include "C_Node.h"
#include "C_Decorator.h"
#include "C_Composite.h"
#include "C_NodeWrapper.h"

namespace wh::xgenaimodule::BehaviorTree {

// ---------------------------------------------------------------------------
// Context structs — per-entity runtime data, heap-allocated by NodeCreator.
//
// UNVERIFIED: exact layouts. Sizes and members inferred from BT semantics.
// Need to RE from NodeCreator<>::AllocateRuntimeData and Update methods.
// ---------------------------------------------------------------------------

struct S_SequenceContext {
    uint32_t m_currentChildIndex;       // which child is currently ticking
    // UNVERIFIED: likely has status tracking
};

struct S_SelectorContext {
    uint32_t m_currentChildIndex;       // which child is currently ticking
    // UNVERIFIED
};

struct S_ParallelContext {
    // UNVERIFIED: likely tracks status of each child independently
    // Parallel ticks ALL children each frame
};

struct S_SwitchContext {
    uint32_t m_activeCase;              // which case/branch is selected
    // UNVERIFIED
};

struct S_GateContext {
    // UNVERIFIED: gate evaluation state
};

struct S_LoopContext {
    uint32_t m_iteration;               // current loop iteration
    uint32_t m_maxIterations;           // -1 for infinite
    // UNVERIFIED
};

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
// Logic classes — stateless policy classes for C_NodeWrapper.
//
// VERIFIED: these add NO data members to the wrapper (all C_Node-based
// wrappers free exactly sizeof(TBase), regardless of TNode).
// Their only role is to define WHICH variables to bind from XML at
// tree construction time (via OnInitialize [14] and RegisterVariables [40]).
//
// The behavioral difference between Sequence/Selector/Parallel is encoded
// in the runtime context (TContext) + the shared C_Composite base logic,
// NOT in these logic classes.
// ---------------------------------------------------------------------------

class C_SequenceLogic {};
class C_SelectorLogic {};
class C_ParallelLogic {};
class C_SwitchLogic {};
class C_LoopLogic {};
class C_IfConditionLogic {};
class C_IfElseConditionLogic {};
class C_FuseBoxLogic {};

// ---------------------------------------------------------------------------
// C_Gate — CRTP wrapper-based conditional gate node.
//
// RTTI: .?AVC_Gate@BehaviorTree@xgenaimodule@wh@@
// Size: 0x68 bytes
// VERIFIED: inherits C_NodeWrapper<C_Gate, C_FixedComposite<2>, S_GateContext>
// ---------------------------------------------------------------------------
class C_Gate : public C_NodeWrapper<C_Gate, C_FixedComposite<2>, S_GateContext> {
public:
    const char* GetNodeCategory() const override { return "Gate"; } // [6]
    // Additional data beyond C_FixedComposite<2> — exact layout UNVERIFIED
    // Total: 0x68 bytes (C_FixedComposite<2> base + gate state)
};

// ---------------------------------------------------------------------------
// Final instantiated node types via C_NodeWrapper.
// ---------------------------------------------------------------------------
using SequenceNode      = C_NodeWrapper<C_SequenceLogic,        C_Composite,         S_SequenceContext>;
using SelectorNode      = C_NodeWrapper<C_SelectorLogic,        C_Composite,         S_SelectorContext>;
using ParallelNode      = C_NodeWrapper<C_ParallelLogic,        C_Composite,         S_ParallelContext>;
using SwitchNode        = C_NodeWrapper<C_SwitchLogic,          C_SwitchBase,        S_SwitchContext>;
using LoopNode          = C_NodeWrapper<C_LoopLogic,            C_Decorator,         S_LoopContext>;
using IfConditionNode   = C_NodeWrapper<C_IfConditionLogic,     C_Decorator,         S_IfConditionContext>;
using IfElseNode        = C_NodeWrapper<C_IfElseConditionLogic,  C_Decorator,         S_IfElseConditionContext>;
using FuseBoxNode       = C_NodeWrapper<C_FuseBoxLogic,         C_FixedComposite<3>, S_FuseBoxContext>;

}  // namespace wh::xgenaimodule::BehaviorTree
