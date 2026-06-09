#pragma once

#include <cstdint>
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeFactory.h"
#include "../NodeAttribute.h"

// ===========================================================================
// C_RemoveItem.h  -  Behavior-tree leaf action node "RemoveItem".
//
// Reverse-engineered from WHGame.dll (KCD1 retail).  Namespace
// wh::xgenaimodule::BehaviorTree.
//
// XML (verified from the schema / attribute-bind pass):
//     <RemoveItem Item="..." Amount="..." FailOnDoesntExist="..." NotifyUI="..."/>
//
// Game role: an action node that removes a quantity of an item from an actor's
// inventory.  This is the node used by the food-poisoning / "poison the pot"
// systems and any AI/quest action that consumes inventory items.
//
// ---------------------------------------------------------------------------
// VERIFIED node-type template instantiation  (from the registration site
// sub_180178C30, the singleton-init at 0x180178d5e — VERBATIM Hex-Rays):
//
//   v2 = pooled_new(0x70);                     // factory singleton, 0x70 bytes
//   *v2    = &C_NodeFactoryImpl< C_RemoveItem,
//                C_DefaultNodeContextCasting<S_RemoveItemContext> >::vftable;
//   v2[1]  = &C_NodeContextPool< S_RemoveItemContext,
//                C_DefaultNodeContextCasting<S_RemoveItemContext> >::vftable;
//   sub_1807128D4(v2+2, 0xA8, 8, ...);         // context-record class: size
//                                              //   0xA8, alignment 8
//   *v2    = &C_NodeFactory_RemoveItem::vftable;// final installed factory vtable
//
//   => The node IS a C_NodeWrapper over the standard machinery, with
//      TNode    = C_RemoveItem
//      TBase    = C_Node                (VERIFIED: leaf, 0x28 - see node ctor)
//      TContext = S_RemoveItemContext   (per-entity runtime data, sizeof 0xA8)
//      TCasting = C_DefaultNodeContextCasting<S_RemoveItemContext>
//   NODE OBJECT (the allocated BT node, distinct from the factory singleton):
//      size 0x28; create thunk sub_1806BBCC8 does alloc(0x28) +
//      _InterlockedExchangeAdd(&dword_183002E60, 0x28u) then ctor sub_1806BBD40;
//      base ctor sub_1806BBDA4 installs the C_NodeWrapper<C_RemoveItem, C_Node,
//      S_RemoveItemContext> vtable then the C_RemoveItem vtable (0x1821f5a80).
//   The factory singleton (0x70 bytes) carries THREE vtables: the
//   C_NodeFactoryImpl<...> factory vtable (+0x00), the C_NodeContextPool<...>
//   vtable (+0x08, folded pool subobject), and the C_NodeFactory_RemoveItem
//   vtable installed last at +0x00.  This matches the verified
//   factory+pool+casting model documented in C_NodeFactory.h / C_NodeContext.h.
//
// ---------------------------------------------------------------------------
// XML -> C++ -> engine call chain  (VERIFIED)
// ---------------------------------------------------------------------------
//   1. Tree XML <RemoveItem ...> is parsed by the node creator registered via
//      C_NodeFactory_RemoveItem (RTTI .?AVC_NodeFactory_RemoveItem@BehaviorTree@
//      xgenaimodule@wh@@ name@0x182aa84b0; factory vtable@0x182333690; created &
//      registered at module-init site 0x180178d5e inside sub_180178C30).  The
//      factory binds the four XML attributes into NodeAttribute<T> members owned
//      by the node creator (Item/Amount -> typed values, FailOnDoesntExist/
//      NotifyUI -> bool).  [UNVERIFIED] exact per-attribute NodeAttribute slot
//      offsets (the per-attribute bind reads were not isolated; see notes).
//
//   2. The node's TNode policy Update (wh::xgenaimodule::BehaviorTree::
//      C_RemoveItem::Update_18044F6B0, sub_18044F69C) reads the per-entity
//      runtime context pointer (node-data key) and looks it up in the entity's
//      context hashmap (hash via sub_1804BF50C, bucket-walk via the map at
//      ctx+0x78/+0x90/+0xA0).  Returns a bool (setnz) — the running/result flag.
//
//   3. The per-entity runtime context ("runner", ctor sub_1804505F4 @
//      0x180450610) derives from wh::xgenaimodule::C_AIObject (its vtable is
//      stored at +0x00) and from C_DynamicLinkableObject (a second vtable is
//      installed at +0x60 by GetActor/sub_180450300).  Its OnInitialize
//      (sub_18045085C @ 0x180450860, phase==1) resolves the owning entity via
//      sub_1803BAE88(g_entitySystem, actorId) and registers inventory listeners
//      by walking entity+0x478 and calling sub_180584F60 per entry.
//
//   4. The actual removal is performed by the C_Inventory remove-core
//      sub_18044F718 (signature: (C_Inventory* inv, Out* result, ItemPtr item,
//      int amount)).  It clamps `amount` to the stack count at item+0x38; when
//      amount == full stack it removes the whole stack (pushes the removed item
//      into a vector at inv+0x60, sets item+0x68, fires the change/notify hook
//      sub_180451DFC(item,0x10,..), applies via sub_18044F7D0, finalises via
//      sub_180452474); when amount < full stack it takes the partial-split path
//      sub_18044F47C which drives the change through an
//      std::function<void(wh::entitymodule::I_InventoryListener*)> callback
//      (the UI/listener notification — gated by the NotifyUI attribute).
//
// ---------------------------------------------------------------------------
// ANCHORS (addresses)
// ---------------------------------------------------------------------------
//   node RTTI name        0x182aa85d0  .?AVC_RemoveItem@BehaviorTree@...@wh@@
//   factory RTTI name     0x182aa84b0  .?AVC_NodeFactory_RemoveItem@...@wh@@
//   factory vtable        0x182333690  (COL resolved from name)
//   factory reg site      0x180178d5e  (module init / node-type registration)
//   node Update           0x18044f6b0  sub_18044F69C   (context lookup, bool)
//   runner Update         0x1804503e0  sub_18045034C
//   runner DoRemove       0x180450038  sub_18044FFF4   (map erase/finalise)
//   runner ctor           0x180450610  sub_1804505F4   (C_AIObject base @+0x00)
//   GetItemId             0x180450230  sub_180450130
//   GetAmount             0x180450250  sub_180450238
//   GetActor              0x180450330  sub_180450300   (installs DLO vtables)
//   NodeData ctor/Init    0x180450860  sub_18045085C   (phase==1 listener reg)
//   inventory remove core 0x18044f718  sub_18044F718   (C_Inventory::RemoveItem)
//   partial-split path    0x18044f47c  sub_18044F47C   (listener-callback path)
//   change/notify hook    0x180451dfc  sub_180451DFC
// ===========================================================================

namespace wh::xgenaimodule::BehaviorTree {

// ---------------------------------------------------------------------------
// S_RemoveItemContext  -  per-entity runtime context for a RemoveItem node.
//
// RTTI (context family convention): a per-entity context allocated when the
// node first runs for an actor; keyed in the entity's BT context hashmap by the
// node-data pointer (read at node+0x68 by Update).  This is NOT stored in the
// node object itself — the node (policy) is stateless; this struct is the
// heap-allocated per-entity state (see C_NodeWrapper.h / C_NodeContext.h model).
//
// LAYOUT (from runner ctor sub_1804505F4 @ 0x180450610 + GetActor
//         sub_180450300 @ 0x180450330):
//   +0x00 C_AIObject vtable           (ctor: *a1 = &C_AIObject::vftable)
//   +0x08 void*      m_pOwner         (ctor: *(a1+8) = *a2  — owner/node back-ptr)
//   +0x10 <fixed container, cap 0xC, elem-stride 3>   (ctor: sub_1804217C8(
//                                       a1+0x10, 0xC, 3, sub_1802E7190))
//   +0x34 uint32_t   m_actorId        (ctor: = 0xFFFFFFFF; an item/actor WUID slot)
//   +0x38 uint32_t   m_field38        (ctor: = 0xFFFFFFFF)  [UNVERIFIED meaning]
//   +0x40 void*      m_field40        (ctor: = 0)
//   +0x48 void*      m_field48        (ctor: = 0)
//   +0x50 uint16_t   m_field50        (ctor: = 0)           [UNVERIFIED width/use]
//   +0x58 void*      m_pCreatorOrCtx  (ctor: = a3)
//   +0x60 C_DynamicLinkableObject vtable (installed by GetActor sub_180450300:
//                                       *(this+0x60) = &C_DynamicLinkableObject::
//                                       vftable_0 — second polymorphic subobject)
//   ... +0x68 .. +0xF8 : an embedded hash-map (the WUID->entry table walked by
//                        DoRemove/GetItemId via sub_1804BF50C + sub_180207188;
//                        fields at +0x68 head, +0xC8/+0xD8 secondary table,
//                        +0xF0 element-record base).  [UNVERIFIED exact std type
//                        and full member breakdown — the map internals were read
//                        as raw offsets, not resolved to a named container.]
//
// [UNVERIFIED] total sizeof.  The map subobject extends past +0xF8 and its tail
// was not bounded under the stalled tooling.  Treated as opaque below the
// documented head so the layout above is not over-asserted.
// ---------------------------------------------------------------------------
struct S_RemoveItemContext {
    inline static constexpr auto RTTI = Offsets::RTTI_S_RemoveItemContext;
    // NOTE: this is a forward layout sketch.  The two polymorphic bases
    // (C_AIObject at +0x00 and C_DynamicLinkableObject at +0x60) are real but
    // are not redefined here to avoid duplicating types that live in
    // xgenaimodule core headers; include those and inherit once they exist.
    void*    m_aiObjectVtable;   // +0x00  &wh::xgenaimodule::C_AIObject::vftable
    void*    m_pOwner;           // +0x08  owner / node back-pointer (= *a2)
    uint8_t  m_fixedContainer[0x24]; // +0x10..+0x33  cap-0xC/stride-3 container
    uint32_t m_actorOrItemId;    // +0x34  WUID slot (init 0xFFFFFFFF)
    uint32_t m_field38;          // +0x38  (init 0xFFFFFFFF)  [UNVERIFIED]
    void*    m_field40;          // +0x40  (init 0)
    void*    m_field48;          // +0x48  (init 0)
    uint16_t m_field50;          // +0x50  (init 0)            [UNVERIFIED]
    uint8_t  _pad52[6];          // +0x52  alignment
    void*    m_pCreatorOrCtx;    // +0x58  (= ctor arg a3)
    void*    m_dloVtable;        // +0x60  &C_DynamicLinkableObject::vftable
    // +0x68 .. : embedded WUID->entry hashmap (opaque here) [UNVERIFIED tail]
    uint8_t  m_contextMap[0x98]; // +0x68..+0xFF  raw map region (see notes)
};

// ---------------------------------------------------------------------------
// C_RemoveItem  -  the BT leaf action node.
//
// RTTI: .?AVC_RemoveItem@BehaviorTree@xgenaimodule@wh@@  (name@0x182aa85d0)
//
// Like the other Warhorse BT action nodes, C_RemoveItem is a stateless policy
// wrapped by C_NodeWrapper<TNode, TBase, TContext>: the node object is a
// C_Node-sized (0x28) leaf whose vtable slots (Update/OnInitialize/OnTerminate)
// are the inlined policy methods; per-entity mutable state lives in
// S_RemoveItemContext (above), NOT in the node.  The node carries only the
// XML-bound NodeAttributes (which actually live in the node *creator*, the
// factory product — see C_NodeFactory.h).
//
// Update (sub_18044F69C @ 0x18044f6b0): looks up the per-entity
// S_RemoveItemContext in the entity context map and returns the running/result
// status as a bool.  The driving removal goes through the runner Update
// (sub_18045034C) -> C_Inventory remove core (sub_18044F718).
//
// VERIFIED (2026-05) the node template instantiation and object size:
//   node  C_NodeWrapper<C_RemoveItem, C_Node, S_RemoveItemContext>  (leaf, 0x28)
//   base ctor sub_1806BBDA4 installs that wrapper vtable then the C_RemoveItem
//   vtable (0x1821f5a80); node ctor sub_1806BBD40 writes ONLY the C_Node fields
//   (m_pNodeData=0 @+0x10, m_nodeId @+0x18, m_pCreator=0 @+0x20) - nothing past
//   +0x20; create thunk sub_1806BBCC8 allocs 0x28 and adds 0x28 to the
//   dword_183002E60 accounting global (size double-confirmed).
// [UNVERIFIED] the exact vtable slot indices of the policy methods (interfuscator
// slot shuffle) and the per-attribute storage offsets inside the creator.
// ---------------------------------------------------------------------------
class C_RemoveItem
    : public C_NodeWrapper<C_RemoveItem, C_Node, S_RemoveItemContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_RemoveItem;
    // No own data members - object == sizeof(C_Node) == 0x28 (VERIFIED above).
    //
    // The four <RemoveItem .../> XML attributes (Item / Amount /
    // FailOnDoesntExist / NotifyUI) are NOT stored on this node.  They are owned
    // by the node CREATOR (the C_NodeFactory_RemoveItem product - a separate
    // 0x70 factory singleton) and consulted at run time.  Modelling them as node
    // members here would inflate the node past its verified 0x28 size, so they
    // are documented only (XML schema + meanings) in the banner above.
};
static_assert(sizeof(C_RemoveItem) == 0x28);

// ---------------------------------------------------------------------------
// C_NodeFactory_RemoveItem  -  node creator/factory for <RemoveItem>.
//
// RTTI: .?AVC_NodeFactory_RemoveItem@BehaviorTree@xgenaimodule@wh@@
//       (name@0x182aa84b0; vtable@0x182333690; registered @ 0x180178d5e)
//
// Builds a C_RemoveItem node from the XML element and binds the four
// NodeAttributes above from the element's attributes.  See C_NodeFactory.h for
// the shared factory base model.
// ---------------------------------------------------------------------------
// (Declared as a typedef over the shared factory template to avoid redefining
//  the factory base; the concrete node type is C_RemoveItem.)
//   using C_NodeFactory_RemoveItem = C_NodeFactoryImpl<C_RemoveItem>;
// [UNVERIFIED] the exact factory template form — reuse C_NodeFactory.h's
// declaration rather than re-stating it here.

}  // namespace wh::xgenaimodule::BehaviorTree
