// ============================================================================
//  wh::xgenaimodule::BehaviorTree  —  C_GetItemType
//  Behaviour-tree leaf node (system: poison / item classification).
// ----------------------------------------------------------------------------
//  PURPOSE (per task brief)
//    C_GetItemType is the behaviour-tree leaf the poison system uses to classify
//    an item: it reads an item referenced by one brain/blackboard variable, looks
//    up its classification (Category / Type / SubType) in the item database, and
//    writes the colon-joined result (e.g. "food:poison") into a second
//    blackboard variable so the tree can branch on it.
//
//  ── WHAT IS VERIFIED vs. NOT (read this first) ──────────────────────────────
//  VERIFIED (binary string table via find_regex/get_string + direct mangled-name
//  parsing; WHGame.dll, imagebase 0x180000000):
//      * the node / wrapper / factory / context-pool / context-struct RTTI names
//        and addresses (listed below);
//      * from the wrapper mangled name, the COMPLETE template instantiation and
//        therefore the node's base chain and per-instance context type.
//
//  NOT VERIFIED this session (deliberately omitted rather than guessed):
//      * the concrete vtable address and slot-by-slot policy methods,
//      * the constructor and the field offsets / size of S_GetItemTypeContext,
//      * the factory GetContextSize value,
//      * the item-database lookup chain and the exact "Category:Type:SubType"
//        formatting, and the XML attribute names.
//    Repeated vtable/ctor resolution attempts in this session kept landing on
//    MISATTRIBUTED functions (an unrelated `charNode` vtable, CryEngine CSystem
//    shutdown code, and a JUnit-XML unit-test writer), so none of those bodies
//    can be trusted as C_GetItemType's. Every such item is tagged [UNVERIFIED]
//    and must be re-derived (resolve the wrapper RTTI COL @ 0x18250edd4 — the
//    signature==1 COL whose typeDescriptor RVA matches 0x182a8df20 — to its
//    vtable, then decompile the ctor and the policy slots).
//
//  ── RTTI / address evidence (all VERIFIED) ──────────────────────────────────
//    Node type name string
//        ".?AVC_GetItemType@BehaviorTree@xgenaimodule@wh@@"               @ 0x182a8dfd0
//        (type descriptor @ 0x182a8dfc0). No standalone node vtable — the live
//        runtime type is the C_NodeWrapper below.
//
//    Concrete wrapper name string (the live runtime type)
//        ".?AV?$C_NodeWrapper@VC_GetItemType@BehaviorTree@xgenaimodule@wh@@
//          VC_Node@234@US_GetItemTypeContext@234@@BehaviorTree@xgenaimodule@wh@@"
//                                                                         @ 0x182a8df30
//        (type descriptor @ 0x182a8df20; its signature==1 COL @ 0x18250edd4).
//      => Read DIRECTLY from the mangled template arguments:
//             TNode    = C_GetItemType          (stateless behaviour policy)
//             TBase    = C_Node                 (leaf node base, 0x28 bytes)
//             TContext = S_GetItemTypeContext   ('U' => a struct: per-instance data)
//
//    Factory singleton name string
//        ".?AV?$C_NodeFactoryImpl@VC_GetItemType@BehaviorTree@xgenaimodule@wh@@
//          V?$C_DefaultNodeContextCasting@US_GetItemTypeContext@BehaviorTree
//          @xgenaimodule@wh@@@234@@BehaviorTree@xgenaimodule@wh@@"         @ 0x182a8de10
//      => C_NodeFactoryImpl<C_GetItemType,
//                           C_DefaultNodeContextCasting<S_GetItemTypeContext>>.
//
//    Context pool name string
//        ".?AV?$C_NodeContextPool@US_GetItemTypeContext@BehaviorTree@xgenaimodule
//          @wh@@V?$C_DefaultNodeContextCasting@US_GetItemTypeContext@...@@..."
//                                                                         @ 0x182a8dd30
//      => C_NodeContextPool<S_GetItemTypeContext,
//                           C_DefaultNodeContextCasting<S_GetItemTypeContext>>.
//
//    Context struct type-descriptor name string
//        ".?AUS_GetItemTypeContext@BehaviorTree@xgenaimodule@wh@@"        @ 0x182a8f170
//        ('U' => a struct; per-instance runtime data, not the node object).
//
//  This places C_GetItemType in the established machinery (see C_NodeFactory.h,
//  C_NodeContext.h, C_NodeWrapper.h): the factory builds a 0x28 C_Node leaf whose
//  vtable is C_NodeWrapper<C_GetItemType, C_Node, S_GetItemTypeContext>::vftable;
//  the stateless C_GetItemType policy is folded into that vtable; mutable per-
//  tree-instance state lives in the pooled S_GetItemTypeContext, handed to the
//  policy as the opaque UpdateContext.runtimeData and cast back via
//  C_DefaultNodeContextCasting<S_GetItemTypeContext>.
//
//  Node naming convention: wh::xgenaimodule::BehaviorTree::C_GetItemType::<fn>_<addr>
// ============================================================================
#pragma once
#include <cstdint>

#include "../I_Node.h"          // I_Node (60-slot BT node interface) / E_NodeStatus
#include "../C_Node.h"          // C_Node (0x28 leaf base) — VERIFIED base of this node
#include "../C_NodeWrapper.h"   // C_NodeWrapper<TNode, TBase, TContext>
#include "../C_NodeContext.h"   // S_BaseNodeContext, C_DefaultNodeContextCasting,
                             //   C_NodeContextPool
#include "../C_NodeFactory.h"   // C_NodeFactoryImpl<TNode, TCasting>

namespace wh { namespace xgenaimodule { namespace BehaviorTree {

// ----------------------------------------------------------------------------
// S_GetItemTypeContext
//   Per-(tree-instance) runtime data for one C_GetItemType node. Heap-allocated
//   in this node's C_NodeContextPool<S_GetItemTypeContext, ...> and handed to the
//   policy methods as the opaque UpdateContext.runtimeData (cast back via
//   C_DefaultNodeContextCasting<S_GetItemTypeContext>).
//
//   VERIFIED (from the mangled names): this is a 'struct' (RTTI 'U' tag, type
//   descriptor name @ 0x182a8f170) named S_GetItemTypeContext, and it is the 3rd
//   template argument of the node's C_NodeWrapper and the element type of the
//   node's C_NodeContextPool. It therefore derives from S_BaseNodeContext (the
//   verified root of every BT node context; see C_NodeContext.h).
//
//   [UNVERIFIED] all data members and the exact size. The factory GetContextSize
//   (== sizeof(S_GetItemTypeContext), drives the pool stride) and the context
//   ctor / field writes were NOT confirmed this session. The poison use-case
//   implies it caches the resolved item/entity handle that the node's
//   OnInitialize fills and Update/OnTerminate read/reset, but the offsets,
//   widths and sentinel values are NOT confirmed. No members are declared and no
//   sizeof static_assert is emitted, to avoid presenting a guessed layout.
// ----------------------------------------------------------------------------
struct S_GetItemTypeContext : public S_BaseNodeContext
{
    inline static constexpr auto RTTI = Offsets::RTTI_S_GetItemTypeContext;
    // [UNVERIFIED] members — re-derive from the wrapper ctor + policy slots.
    // (Expected per the poison use-case but NOT confirmed: a cached resolved
    //  item/entity handle with a -1 sentinel.)
};

// ----------------------------------------------------------------------------
// C_GetItemType — stateless behaviour policy (TNode).
//
//   Carries NO data members and has NO standalone vtable: it is the compile-time
//   policy folded into C_NodeWrapper<C_GetItemType, C_Node, S_GetItemTypeContext>
//   (see C_NodeWrapper.h). Its RTTI name string (@ 0x182a8dfd0) exists only for
//   type identification; the live object is the wrapper. Per-instance mutable
//   state lives in S_GetItemTypeContext, NOT here; the XML-bound configuration
//   (source / output blackboard variables) lives in the node-data block
//   (C_Node::m_pNodeData, +0x10), NOT in this policy.
//
//   The method declarations below follow the verified C_NodeWrapper policy
//   contract (OnInitialize / Update / OnTerminate over the TContext) so the type
//   is usable. The METHOD BODIES are [UNVERIFIED] this session (see the banner
//   honesty note); the precise read/lookup/format/store semantics still require
//   decompiling the wrapper's vtable slots after a correct COL->vtable resolve.
// ----------------------------------------------------------------------------
class C_GetItemType
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_GetItemType;
    using RuntimeData = S_GetItemTypeContext;

    // [UNVERIFIED] body. Per the C_NodeWrapper contract and the poison use-case:
    // lazily resolve the source blackboard variable into the runtime context.
    static void OnInitialize(S_GetItemTypeContext& ctx) noexcept;

    // [UNVERIFIED] body. Per the use-case: look up the referenced item, read its
    // Category/Type/SubType from the item DB, format "Category:Type[:SubType]"
    // and store it into the output blackboard variable; return Success/Failure.
    // The exact return mapping was NOT verified.
    static E_NodeStatus Update(S_GetItemTypeContext& ctx) noexcept;

    // [UNVERIFIED] body. Per the contract: reset the cached runtime state.
    static void OnTerminate(S_GetItemTypeContext& ctx) noexcept;

    // No data members — stateless policy.
};

// ----------------------------------------------------------------------------
// C_GetItemTypeNode — the live behaviour-tree object.
//   VERIFIED from the wrapper RTTI name @ 0x182a8df30. A 0x28-byte C_Node leaf
//   (no children); the C_GetItemType policy supplies OnInitialize / Update /
//   OnTerminate via the wrapper's vtable overrides. Use this alias to refer to
//   the instantiated node type. ([UNVERIFIED] concrete vtable address.)
// ----------------------------------------------------------------------------
using C_GetItemTypeNode =
    C_NodeWrapper<C_GetItemType, C_Node, S_GetItemTypeContext>;

// ----------------------------------------------------------------------------
// C_GetItemTypeFactory — the per-type creator singleton.
//   VERIFIED from the factory RTTI name @ 0x182a8de10:
//     C_NodeFactoryImpl<C_GetItemType,
//                       C_DefaultNodeContextCasting<S_GetItemTypeContext>>.
//   Builds C_GetItemTypeNode instances and owns the
//   C_NodeContextPool<S_GetItemTypeContext, ...> (pool RTTI name @ 0x182a8dd30)
//   backing the per-instance S_GetItemTypeContext slots. See C_NodeFactory.h /
//   C_NodeContext.h for the shared machinery. ([UNVERIFIED] concrete vtable
//   address and GetContextSize value.)
// ----------------------------------------------------------------------------
using C_GetItemTypeFactory =
    C_NodeFactoryImpl<C_GetItemType,
                      C_DefaultNodeContextCasting<S_GetItemTypeContext> >;

// ----------------------------------------------------------------------------
// [UNVERIFIED] S_GetItemTypeNodeData — the per-node (shared across instances)
//   XML-bound configuration referenced by C_Node::m_pNodeData (+0x10). The
//   poison use-case requires (at least) a source blackboard-variable id (the
//   item to classify) and an output blackboard-variable id (where the joined
//   "Category:Type:SubType" string is written). The exact attribute NAMES,
//   field OFFSETS and TYPES were NOT verified this session and are intentionally
//   omitted to avoid presenting guesses as facts. Re-derive from the factory's
//   CreateNode / node-data XML-binding path for this node type.
// ----------------------------------------------------------------------------

}}} // namespace wh::xgenaimodule::BehaviorTree
