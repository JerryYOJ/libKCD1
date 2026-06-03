#pragma once
// =====================================================================================
//  wh::xgenaimodule::BehaviorTree::C_Expression  (KCD1 retail WHGame.dll, system: flow)
// =====================================================================================
//
//  A leaf behavior-tree node that evaluates one or more "Expressions" (variable
//  assignments / arithmetic) against the per-entity AI blackboard. Authored in BT XML as:
//
//      <Expression expressions="$x = $y, $hp = $hp + 1," />
//
//  Implementation: like every concrete WH BT node, C_Expression is a thin structural shell
//  whose real behavior is provided by a stateless policy compiled into a
//  C_NodeWrapper<...> vtable. The node's OnInitialize/OnTerminate handlers move named
//  blackboard variables ($vars) between the AI knowledge store and a per-entity
//  S_ExpressionContext, where the compiled expressions read/write them.
//
//  -------------------------------------------------------------------------------------
//  RTTI / construction — VERIFIED (absolute addrs, image base 0x180000000)
//  -------------------------------------------------------------------------------------
//   Node RTTI name @ 0x182a910e0  ".?AVC_Expression@BehaviorTree@xgenaimodule@wh@@"
//   Type descriptor @ 0x182a910d0  (name_addr - 0x10)
//   Class-hierarchy desc @ 0x182512340 : numBases=4, single-inheritance chain
//       C_Expression -> C_Node -> I_Node -> I_CastableIface   (CHD base names read; verified)
//   Complete-Object-Locators (3 data xrefs to the type descriptor, all matches_td_rva):
//       COL @ 0x18244b998  offset 0 -> primary vtable  0x1821c0f00  (I_Node, 60 slots)
//       COL @ 0x18244b9c0  offset 8 -> secondary vtable 0x1821c0ec8 (I_DebugNode, 8 slots)
//       COL @ 0x18251022c  offset 0 -> throw/_CatchableType-style entry (no vtable)
//
//   THE decisive evidence (init routine, decompiled) —
//   wh::...::C_Expression::initMembers_18130C170 stores, then patches, the vtables:
//       *(obj+0x00) = &C_NodeWrapper<C_Expression, C_Node, S_ExpressionContext>::vftable;
//       *(obj+0x08) = &C_NodeWrapper<C_Expression, C_Node, S_ExpressionContext>::vftable;
//       *(obj+0x10) = 0;     // m_pNodeData
//       *(obj+0x18) = 0;     // m_nodeId
//       *(obj+0x20) = 0;     // m_pCreator
//       (static sub-policy init) ...
//       *(obj+0x00) = &C_Expression::vftable;     // final primary vtable 0x1821c0f00
//       *(obj+0x08) = &C_Expression::vftable;     // final I_DebugNode  vtable 0x1821c0ec8
//   => the wrapper template is exactly
//      C_NodeWrapper<C_Expression, C_Node, S_ExpressionContext>  (VERIFIED from the symbol).
//
//   Constructor          wh::...::C_Expression::ctor_180585BA4 :
//       obj = operator new(0x28);   // -> object size 0x28 VERIFIED
//       if (!obj) return 0;
//       initSub_180585C2C(obj, creator);
//       *(obj+0x00) = &C_Expression::vftable; *(obj+0x08) = &C_Expression::vftable;
//   Factory               wh::...::C_NodeFactory_Expression
//       (RTTI name @ 0x182a90ff0 ".?AVC_NodeFactory_Expression@BehaviorTree@xgenaimodule@wh@@")
//       descriptor block @ 0x182a91000 : +0x10 = node vtable 0x1821c0f00,
//                                        +0x18 = factory Create thunk -> ctor_180585BA4.
//       NOTE: it is a PLAIN named class "C_NodeFactory_Expression", NOT the templated
//       "C_NodeFactoryImpl<C_Expression>" form. Reconcile with C_NodeFactory.h.
//
//  -------------------------------------------------------------------------------------
//  Object layout (size 0x28; identical to C_Node) — VERIFIED
//  -------------------------------------------------------------------------------------
//   +0x00  vtable (I_Node / C_Expression)   -> 0x1821c0f00
//   +0x08  vtable (I_DebugNode)             -> 0x1821c0ec8
//   +0x10  m_pNodeData : void*  (inherited C_Node; 0 for this node — see below)
//   +0x18  m_nodeId    : uint32 (inherited C_Node)
//   +0x1C  _pad
//   +0x20  m_pCreator  : void*  (inherited C_Node)
//   No data members beyond C_Node: sizeof(C_NodeWrapper<...>) == sizeof(C_Node).
//
//  -------------------------------------------------------------------------------------
//  Runtime behavior — VERIFIED (primary I_Node vtable 0x1821c0f00, slots lookup_funcs-checked)
//  -------------------------------------------------------------------------------------
//  Per C_NodeWrapper.h, the stateless TNode (C_Expression policy) methods are INLINED into
//  the wrapper's vtable entries. The two policy slots that carry this node's $var logic:
//
//   slot 14  OnInitialize  wh::...::C_Expression::OnInitialize_181323E30 :
//       if (!ParserReady_18153F368()) return false;
//       // Three parallel attribute tables describe the $vars this node touches:
//       //   xmmword_1836EDB50  (stride 0x10) — "load into context" group A
//       //   xmmword_1836EDB68  (stride 0x04) — group B (stored via member vfunc +0x18)
//       //   xmmword_1836EDB80  (stride 0x04) — group C
//       // For each entry whose source variable exists (knowledge vfunc +0xF0 test):
//       //   raw = knowledge->GetVarText(+0xE8); h = StringHash(raw);
//       //   write h into S_ExpressionContext at  (ctxBase + table[i].offset);
//       // i.e. it snapshots referenced blackboard variables into the per-entity context.
//   slot 15  OnTerminate   wh::...::C_Expression::OnTerminate_18132D4E0 :
//       // Mirror of OnInitialize over the same three tables: reads each variable back OUT of
//       // S_ExpressionContext (ctxBase + table[i].offset) and writes it to the destination
//       // sink (vfunc +0x218 / +0x10), i.e. commits the assignment results to the blackboard.
//   slot 27  TickNode/driver wh::...::C_Node::Tick_18057FD34  (shared C_Node state machine):
//       status=Running; call vfunc +0x1C0 (the node's Update path); if status in {Success,
//       Failure} run completion (vfunc +0xA0) and child cleanup. Generic; not node-specific.
//   slot 0   (0x1807014a0) scalar deleting destructor.
//   slot 6 / slot 9        guard_purecall — leaf GetNodeCategory / GetChildCount (C_Node).
//   slots 11,48,49,50,51,53,55,56,58,59  _guard_check_icall_nop — leaf no-op callbacks (C_Node).
//
//   XML -> C++ -> engine call chain (one line, verified shape):
//     <Expression expressions="$x=$y,"> --(factory C_NodeFactory_Expression ->
//     ctor_180585BA4, operator new(0x28))--> node. On enter,
//     OnInitialize_181323E30 hashes the referenced $vars out of the AI knowledge store into
//     S_ExpressionContext; the compiled expressions evaluate against that context; on exit
//     OnTerminate_18132D4E0 writes the resulting $vars back to the knowledge store.
//
//  Function naming convention: wh::xgenaimodule::BehaviorTree::C_Expression::<func>_<addr>
// =====================================================================================

#include <cstdint>
#include "../C_Node.h"          // C_Node : I_Node, I_DebugNode  (verified base, size 0x28)

namespace wh { namespace xgenaimodule { namespace BehaviorTree {

namespace Expressions { class I_Expression; }   // fwd; see companion section

// -------------------------------------------------------------------------------------
//  S_ExpressionContext  -- per-entity runtime state for one C_Expression instance.
//  CONFIRMED to exist as a named struct by RTTI:
//      ".?AUS_ExpressionContext@BehaviorTree@xgenaimodule@wh@@"   (get_bytes verified)
//  It is the TContext of C_NodeWrapper<C_Expression, C_Node, S_ExpressionContext> (VERIFIED
//  from the wrapper's mangled symbol in initMembers_18130C170): per-entity heap data, NOT
//  stored inside the node object.
//
//  VERIFIED usage (OnInitialize/OnTerminate slots 14/15): three attribute tables describe a
//  set of named $vars, each with a byte offset into this context. OnInitialize writes the
//  StringHash of each source variable into (this + offset); OnTerminate reads it back out
//  and commits it to the blackboard. So the context holds, per referenced $var, a slot keyed
//  by its compile-time offset.
//
//  [UNVERIFIED] Exact total size and the per-field layout (the attribute-table offset values
//  in xmmword_1836EDB50/B68/B80 were not enumerated). Declared opaque so the type name
//  resolves without asserting wrong offsets; fill in by dumping those three tables.
// -------------------------------------------------------------------------------------
struct S_ExpressionContext
{
    // [UNVERIFIED] members — per-$var hashed-value slots at compile-assigned offsets.
    // Layout/size not enumerated. Placeholder; do not size-assert.
};

// -------------------------------------------------------------------------------------
//  C_Expression  : C_Node   (flow leaf node)
//
//  The concrete node is instantiated as
//      C_NodeWrapper<C_Expression, C_Node, S_ExpressionContext>
//  (VERIFIED). C_Expression here is the stateless policy whose OnInitialize/OnTerminate are
//  inlined into the wrapper vtable (slots 14/15). The object is sizeof(C_Node) == 0x28 with
//  no policy data members; all per-entity state lives in S_ExpressionContext.
// -------------------------------------------------------------------------------------
class C_Expression : public C_Node
{
public:
    // ---- overridden virtual behavior (indices = primary I_Node vtable slots) ----

    // slot 0  (0x1807014a0) scalar deleting destructor.
    virtual ~C_Expression();

    // slot 14 (0x181323e30) OnInitialize: snapshot referenced $vars from the AI knowledge
    //          store into S_ExpressionContext (string-hashed, keyed by compile-time offset).
    void OnInitialize(void * context) /*override [14]*/;

    // slot 15 (0x18132d4e0) OnTerminate: write the resulting $vars from S_ExpressionContext
    //          back out to the AI knowledge store (commit assignments).
    void OnTerminate(void * context) /*override [15]*/;

    // NOTE: GetNodeCategory [6] / GetChildCount [9] are purecall (leaf); the child-lifecycle
    //       and suspend slots are guard_nop — all inherited unchanged from C_Node. The shared
    //       state-machine driver Tick lives at slot 27 (C_Node::Tick_18057FD34). Only the two
    //       slots above carry expression-node-specific logic.

public:
    // ---- XML attribute bound for <Expression> ----
    static constexpr const char * kAttrTag         = "Expression";   // BT node tag
    static constexpr const char * kAttrExpressions = "expressions";  // compiled expression list
};
static_assert(sizeof(C_Expression) == 0x28, "C_Expression must remain C_Node size (0x28)");


// =====================================================================================
//  COMPANION SECTION -- the Expressions layer (wh::xgenaimodule::BehaviorTree::Expressions)
//  How `$var` assignment + common ops compile and run. CONCISE overview; the full operator
//  set is intentionally NOT reverse-engineered here.
// =====================================================================================
namespace Expressions {

// -------------------------------------------------------------------------------------
//  I_Expression  -- interface implemented by every compiled expression node.
//    RTTI name @ 0x182a85580  ".?AVI_Expression@Expressions@BehaviorTree@xgenaimodule@wh@@"
//    (VERIFIED). Note the extra "Expressions" namespace segment: the expression sub-system
//    lives in wh::xgenaimodule::BehaviorTree::Expressions, a child of the BT namespace.
//    [UNVERIFIED] vtable address / slot order (Evaluate index & signature) were not resolved
//    in this pass; an earlier attempt's vtable came from a faulty type-descriptor scan and
//    is RETRACTED. EXPECTED: an Evaluate(context, ...) virtual invoked while the node ticks.
// -------------------------------------------------------------------------------------
class I_Expression
{
public:
    virtual ~I_Expression() = default;                                  // [UNVERIFIED slot]
    // [UNVERIFIED] virtual <result> Evaluate(S_ExpressionContext*, /*tick*/ void*) = 0;
};

// -------------------------------------------------------------------------------------
//  C_CompiledExpressionWrapper  -- the concrete I_Expression the compiler emits; wraps a
//    parsed expression and is the runtime form of one compiled "expressions" entry.
//    RTTI name @ 0x182a85e90
//      ".?AVC_CompiledExpressionWrapper@Expressions@BehaviorTree@xgenaimodule@wh@@" (VERIFIED)
//    [UNVERIFIED] template arguments, member layout (inner-expr storage offset), and the
//    Evaluate forwarder were not confirmed (vtable not re-resolved after retracting the bad
//    scan). EXPECTED design: holds an inner expression and forwards Evaluate to it.
// -------------------------------------------------------------------------------------
class C_CompiledExpressionWrapper : public I_Expression
{
    // [UNVERIFIED] layout and wrapped-expression member.
};

//  $var assignment + common operators
//  ---------------------------------
//  "$x = $y" (and +, -, comparisons, quest/game built-ins) compile into concrete
//  I_Expression node classes. Evaluating an assignment resolves the right-hand expression to
//  a value and writes it into the named blackboard variable ($x). The variables themselves
//  are the string-hashed entries that C_Expression::OnInitialize stages into
//  S_ExpressionContext and C_Expression::OnTerminate commits back (see node section above).
//
//  [UNVERIFIED] The concrete operator class set and the MathOperations / QuestFunctions
//  dispatch tables (operator/function token -> C_*Expr factory during compilation of the
//  "expressions" string) were NOT enumerated. Out of scope for this header.

} // namespace Expressions


// -------------------------------------------------------------------------------------
//  [UNVERIFIED]  -- items not proven by direct analysis in this pass:
//   * S_ExpressionContext total size and per-field offsets (the three attribute tables
//     xmmword_1836EDB50 / _B68 / _B80 that define them were not dumped).
//   * m_pNodeData (+0x10) usage for THIS node: initMembers sets it to 0 and the verified
//     slots 14/15 do not read it; whether a compiled-tree pointer is later attached via
//     SetNodeData/LoadFromXml was not traced. Modeled as inherited C_Node field, 0 at init.
//   * I_Expression vtable address and Evaluate slot index/offset/signature (RETRACTED prior
//     guess; not re-resolved).
//   * C_CompiledExpressionWrapper template args, member layout, and Evaluate forwarder.
//   * MathOperations / QuestFunctions tables and the full operator/function catalogue
//     (intentionally out of scope).
//   * Engine vfunc identities used inside OnInitialize/OnTerminate (+0xE8 GetVarText, +0xF0
//     HasVar, +0x218/+0x10/+0x18 sinks) are inferred from call shape, not separately named.
//
//   Task-prompt mismatches confirmed during RE (worth noting):
//   * Factory is the plain class C_NodeFactory_Expression, NOT templated C_NodeFactoryImpl.
//   * The Expressions sub-system is in a CHILD namespace
//     wh::xgenaimodule::BehaviorTree::Expressions (per the verified mangled names), not the
//     flat BehaviorTree namespace.
//
//   PRIOR-SESSION RETRACTION: an earlier resolution used a buggy type-descriptor dword-scan
//   that produced false-positive vtables (matches were ASCII bytes inside RTTI name strings)
//   and pointed at unrelated combat/geometry math. All claims derived from it — specific
//   slot indices like "Update=slot22 / LoadFromXml=slot27 / HandleEvent=slot37", the
//   S_ExpressionData{m_pCompiled@+8} struct, the "C_AssignExpr" instantiation, and the
//   I_Expression/CCEW Evaluate-at-+0x10 forwarder — are RETRACTED and are NOT asserted here.
// -------------------------------------------------------------------------------------

}}} // namespace wh::xgenaimodule::BehaviorTree
