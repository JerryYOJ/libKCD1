// ============================================================================
//  wh::xgenaimodule::BehaviorTree :: C_GetItemProperty
//  Behavior-tree LEAF node — reads a property of an inventory/consumable item
//  (poison / inventory system) and writes it into the node's per-instance
//  context for downstream nodes to consume.
// ----------------------------------------------------------------------------
//  WHGame.dll  imagebase 0x180000000  (IDA verified).
//
//  Like every KCD behavior-tree node, C_GetItemProperty is a STATELESS policy
//  class (the "TNode" of C_NodeWrapper, see C_NodeWrapper.h). The live object
//  the engine instantiates is:
//
//      C_NodeWrapper< C_GetItemProperty,         // TNode  (behavior policy)
//                     C_Node,                     // TBase  (leaf, 0x28 bytes)
//                     S_GetItemPropertyContext >  // TContext (per-instance data)
//
//  This is VERIFIED two independent ways:
//    (a) the node primary vtable @ 0x1821ff850 and the I_DebugNode secondary
//        vtable @ 0x1821ff888 both have an RTTI CompleteObjectLocator whose
//        typeDescriptor is 0x182a99de0 = ".?AVC_GetItemProperty@...";
//    (b) the factory ctor sub_18016E500 (below) and the attribute dtor
//        sub_18063F15C name the wrapper/impl/context/attribute types in full.
//
//  ── Object layout (C_Node leaf, 0x28; standard wrapper, see C_Node.h) ───────
//      +0x00  &C_NodeWrapper<C_GetItemProperty,C_Node,
//                            S_GetItemPropertyContext>::vftable   // I_Node
//      +0x08  (I_DebugNode secondary vtable)
//      +0x10  void*    m_pNodeData
//      +0x18  uint32_t m_nodeId
//      +0x20  void*    m_pCreator
//  The node holds NO per-tick state; all mutable per-tree-instance state lives
//  in the pooled S_GetItemPropertyContext served by the factory's
//  C_NodeContextPool (see C_NodeContext.h).
//
//  ── RTTI evidence (type-descriptor name strings, all confirmed) ────────────
//    C_GetItemProperty             td @ 0x182a99de0  name @ 0x182a99df0
//        ".?AVC_GetItemProperty@BehaviorTree@xgenaimodule@wh@@"
//    C_NodeWrapper<...>            name @ 0x182a99e40
//        ".?AV?$C_NodeWrapper@VC_GetItemProperty@...@VC_Node@234@
//          US_GetItemPropertyContext@234@@..."
//    S_GetItemPropertyContext      td @ 0x182a99ed0  name @ 0x182a99ee0
//        ".?AUS_GetItemPropertyContext@BehaviorTree@xgenaimodule@wh@@" (struct)
//    EnumNodeAttribute<E_ItemProperty,S_GetItemPropertyContext>  name @ 0x182a99f30
//        ".?AV?$EnumNodeAttribute@W4E_ItemProperty@
//          S_GetItemPropertyContext@BehaviorTree@xgenaimodule@wh@@@..."
//        IMPORTANT: the dtor sub_18063F15C spells the value type as
//        "EnumNodeAttribute<enum S_GetItemPropertyContext::E_ItemProperty>",
//        i.e. E_ItemProperty is a NESTED enum of S_GetItemPropertyContext, and
//        the attribute base is NodeAttributeBase (see NodeAttribute.h).
//    C_NodeFactory_GetItemProperty td @ 0x182a99ca0  name @ 0x182a99cb0
//        ".?AVC_NodeFactory_GetItemProperty@BehaviorTree@xgenaimodule@wh@@"
//    C_NodeFactoryImpl<C_GetItemProperty,
//                      C_DefaultNodeContextCasting<S_GetItemPropertyContext>>
//                                  name @ 0x182a99d10
//    C_NodeContextPool<S_GetItemPropertyContext,...>  name @ 0x182a98510
//
//  ── VTABLE evidence (each vtable resolved via its COL -> typeDescriptor) ────
//    NODE primary vtable     @ 0x1821ff850  COL -> td 0x182a99de0 (C_GetItemProperty)
//    NODE I_DebugNode vtable @ 0x1821ff888  COL -> td 0x182a99de0 (C_GetItemProperty)
//    CONTEXT vtable          @ 0x1821cfc98  COL -> td 0x182a99ed0 (S_GetItemPropertyContext)
//    EnumAttr vtable         @ 0x1821cfcb8  (EnumNodeAttribute<E_ItemProperty,...>;
//                                            collapses to NodeAttributeBase::vftable)
//    FACTORY vtable          @ 0x18232a3a8  COL -> td 0x182a99ca0 (C_NodeFactory_GetItemProperty)
//
//  ── Factory build (VERIFIED ctor sub_18016E500 @ 0x18016e500; names all types)
//    Allocates a 0x70-byte object and installs:
//      +0x00  &C_NodeFactoryImpl<C_GetItemProperty,
//                  C_DefaultNodeContextCasting<S_GetItemPropertyContext>>::vftable
//      +0x08  &C_NodeContextPool<S_GetItemPropertyContext,
//                  C_DefaultNodeContextCasting<S_GetItemPropertyContext>>::vftable
//      +0x10  std::vector-like / pool storage initialized via sub_1807128D4
//             (element size 0x60, alignment 8)
//      +0x00  (re-written) &C_NodeFactory_GetItemProperty::vftable
//    => C_NodeFactory_GetItemProperty IS the factory; it multiply-derives from
//       C_NodeFactoryImpl<...> (primary, +0x00) and embeds/derives the
//       C_NodeContextPool<...> (secondary vtable at +0x08) that allocates the
//       per-instance S_GetItemPropertyContext slots.
//
//  ── Attribute teardown (VERIFIED dtor sub_18063F15C @ 0x18063f15c) ──────────
//      *this = &EnumNodeAttribute<S_GetItemPropertyContext::E_ItemProperty>::vftable;
//      ... (frees an owned buffer at this[2] if non-null) ...
//      *this = &NodeAttributeBase::vftable;                 // base subobject
//    => the node's single XML attribute is an
//       EnumNodeAttribute<E_ItemProperty> : NodeAttributeBase that owns a small
//       heap buffer (the enum token/string table). The exact <token,value> map
//       is NOT a flat array and was not cleanly decoded — see UNVERIFIED.
//
//  ── XML -> C++ -> engine ────────────────────────────────────────────────────
//    The node declares ONE XML attribute: a property selector parsed by the
//    embedded EnumNodeAttribute<E_ItemProperty> into S_GetItemPropertyContext::
//    E_ItemProperty. At tick time the (inlined) Update resolves the referenced
//    item's selected property and writes the result into the context value slot.
//
//  Node-naming convention used in this file:
//    wh::xgenaimodule::BehaviorTree::C_GetItemProperty::<func>_<addr>
// ============================================================================
#pragma once

#include <cstdint>

#include "../C_Node.h"            // C_Node leaf base (0x28), I_Node, E_NodeStatus
#include "../C_NodeWrapper.h"     // C_NodeWrapper<TNode,TBase,TContext>
#include "../C_NodeContext.h"     // S_BaseNodeContext, C_NodeContextPool, casting
#include "../C_NodeFactory.h"     // C_NodeFactoryImpl<...>
#include "../NodeAttribute.h"     // EnumNodeAttribute<TEnum> : NodeAttributeBase

namespace wh { namespace xgenaimodule { namespace BehaviorTree {

// ----------------------------------------------------------------------------
// S_GetItemPropertyContext
//   Per-(tree-instance) runtime data for a C_GetItemProperty node. Owned at
//   runtime by C_NodeContextPool<S_GetItemPropertyContext,...> (RTTI @
//   0x182a98510); the node passes it to the policy as `void* runtimeData`.
//
//   POLYMORPHIC: has its own vtable (0x1821cfc98, COL -> td 0x182a99ed0).
//   Derives from the WH context base S_BaseNodeContext (see C_NodeContext.h),
//   matching the RTTI tag ".?AUS_GetItemPropertyContext@...@@" (a struct).
//
//   It nests the property-selector enum E_ItemProperty (VERIFIED from the
//   attribute type name "EnumNodeAttribute<S_GetItemPropertyContext::
//   E_ItemProperty>" in dtor sub_18063F15C).
//
//   [UNVERIFIED] total sizeof and exact member offsets. The context holds at
//   least the parsed selector and the resolved output value; their precise
//   offsets were not isolated (the per-instance ctor is served by the pool and
//   the value write is inlined into the wrapper Update).
// ----------------------------------------------------------------------------
struct S_GetItemPropertyContext : public S_BaseNodeContext
{
    // ------------------------------------------------------------------------
    // E_ItemProperty — selects which property of the resolved item to read.
    //   Backing type std::int32_t (RTTI "W4E_ItemProperty" == 32-bit int enum).
    //   The value is parsed from the node's XML attribute by the embedded
    //   EnumNodeAttribute<E_ItemProperty>.
    //
    //   [UNVERIFIED] enumerator NAMES and VALUES. The EnumNodeAttribute owns a
    //   heap token table (freed by dtor sub_18063F15C via this[2]) mapping XML
    //   strings to E_ItemProperty values, but it is a WH hashed-string record
    //   structure, not a flat {char*,int} array, and was not cleanly decoded in
    //   this pass. The task hint that "ConsumableBuff" is an E_ItemProperty
    //   value is UNSUPPORTED by evidence (the "ConsumableBuff"/"consumable_buff"
    //   strings are xref'd only by unrelated code: sub_18016CA30 / sub_1801016C0,
    //   NOT by this node/factory/attribute). No enumerators are asserted.
    // ------------------------------------------------------------------------
    enum class E_ItemProperty : std::int32_t
    {
        // [UNVERIFIED] all enumerators — decode the EnumNodeAttribute token
        // table owned by the attribute (heap buffer at attribute+0x10) to fill.
    };

    E_ItemProperty m_property;   // [UNVERIFIED offset] parsed selector
    std::uint32_t  m_value;      // [UNVERIFIED offset] resolved property value
                                 //   (written by Update for downstream nodes)
};

// ----------------------------------------------------------------------------
// C_GetItemProperty
//   The STATELESS behavior policy (TNode). NO data members and NO standalone
//   vtable of its own — VERIFIED: the C_GetItemProperty type descriptor is
//   reachable ONLY through the C_NodeWrapper node vtables (0x1821ff850 primary,
//   0x1821ff888 I_DebugNode secondary). The policy methods are inlined by the
//   wrapper into the shared C_Node-wrapper vtable slots.
//
//   Method contract (the C_NodeWrapper policy interface; bodies inlined):
//     void         OnInitialize(S_GetItemPropertyContext& ctx);
//     E_NodeStatus Update      (S_GetItemPropertyContext& ctx);  // resolves the
//                                  E_ItemProperty selector, writes ctx.m_value
//     void         OnTerminate (S_GetItemPropertyContext& ctx);
//   [UNVERIFIED] the exact property-resolution switch (which item field is read
//   per E_ItemProperty value) — inlined; not isolatable as a named slot.
// ----------------------------------------------------------------------------
class C_GetItemProperty
{
public:
    using Context = S_GetItemPropertyContext;
    // Stateless policy: no data members (does NOT appear in node-object layout).
};
static_assert(sizeof(C_GetItemProperty) == 1,
              "C_GetItemProperty is a stateless behavior policy (no members)");

// ----------------------------------------------------------------------------
// C_GetItemPropertyNode
//   The concrete behavior-tree node the engine instantiates and stores in the
//   compiled tree. A C_Node leaf (0x28) — no extra members in the node itself
//   (per-instance state lives in the pooled S_GetItemPropertyContext).
// ----------------------------------------------------------------------------
using C_GetItemPropertyNode =
    C_NodeWrapper< C_GetItemProperty, C_Node, S_GetItemPropertyContext >;

// ----------------------------------------------------------------------------
// C_NodeFactory_GetItemProperty
//   The named per-node factory (RTTI ".?AVC_NodeFactory_GetItemProperty@...@@",
//   vtable @ 0x18232a3a8). VERIFIED from ctor sub_18016E500: a 0x70-byte object
//   that installs C_NodeFactoryImpl<...>::vftable at +0x00 and
//   C_NodeContextPool<...>::vftable at +0x08, then re-writes +0x00 with its own
//   C_NodeFactory_GetItemProperty::vftable.
//
//   It therefore multiply-derives from the generic
//     C_NodeFactoryImpl< C_GetItemProperty,
//                        C_DefaultNodeContextCasting<S_GetItemPropertyContext> >
//   (RTTI name @ 0x182a99d10, primary base at +0x00) and the per-node
//     C_NodeContextPool< S_GetItemPropertyContext,
//                        C_DefaultNodeContextCasting<S_GetItemPropertyContext> >
//   (RTTI @ 0x182a98510, secondary base whose vtable sits at +0x08) which
//   allocates the per-instance contexts. On XML load it binds the node's single
//   EnumNodeAttribute<E_ItemProperty> selector and creates the
//   C_GetItemPropertyNode.
//
//   [UNVERIFIED] the precise member layout between +0x10 and +0x70 (pool storage
//   initialized via sub_1807128D4 with element size 0x60); modeled here purely
//   through the two base classes — pool/attribute internals live in their own
//   headers (C_NodeFactory.h / C_NodeContext.h).
// ----------------------------------------------------------------------------
class C_NodeFactory_GetItemProperty
    : public C_NodeFactoryImpl< C_GetItemProperty,
                                C_DefaultNodeContextCasting<S_GetItemPropertyContext> >
    , public C_NodeContextPool< S_GetItemPropertyContext,
                                C_DefaultNodeContextCasting<S_GetItemPropertyContext> >
{
public:
    // Single XML attribute bound by this factory: the property selector.
    EnumNodeAttribute<S_GetItemPropertyContext::E_ItemProperty> m_propertyAttr;
    // [UNVERIFIED] m_propertyAttr offset and any additional factory members.
};

}}} // namespace wh::xgenaimodule::BehaviorTree
