#pragma once

#include <cstdint>
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"
#include "../C_NodeFactory.h"
#include "../../I_NoRTTITypeInfo.h"

// ===========================================================================
//  C_InstantSendMessageToNPC  --  Behavior-Tree leaf node (messaging system)
//
//  XML tag:  <InstantSendMessageToNPC ... />
//
//  Sends a Warhorse AI "message" (mailbox event) to a target NPC. The
//  "Instant" prefix (same convention as C_InstantDoPlace / C_InstantDrawWeapon)
//  marks the variant whose send resolves within a single behavior-tree tick.
//  The non-instant sibling C_SendMessageToNPC keeps the node Running until the
//  send/ack completes (the two share a vtable-swap relationship -- see ctor
//  sub_1813925DC, which builds a C_SendMessageToNPC then re-stamps it as a
//  C_InstantSendMessageToNPC).
//
// ---------------------------------------------------------------------------
//  VERIFIED RTTI / VTABLE ANCHORS (WHGame.dll, imagebase 0x180000000)
//
//    Node class type-descriptor name string (find_regex over .rdata):
//      0x182aaca20  ".?AVC_InstantSendMessageToNPC@BehaviorTree@xgenaimodule@wh@@"
//      typeDescriptor = 0x182aaca10 ; COL = 0x18244b0d8
//
//    Node PRIMARY vtable (the I_Node interface subobject, written at obj+0x10):
//      0x1821e7088   (vtable[-1] @ 0x1821e7080 -> COL 0x18244b0d8 -> our TD)
//    Node SECONDARY vtable (also under our TD, COL 0x18244b100): 0x1821e7050
//    The ctor also references the named vftables:
//      wh::xgenaimodule::I_NoRTTITypeInfo::vftable         (obj +0x00)
//      wh::xgenaimodule::BehaviorTree::I_DebugNode::vftable (obj +0x08)
//      wh::xgenaimodule::BehaviorTree::C_Node::vftable       (interface base)
//      wh::xgenaimodule::BehaviorTree::C_SendMessageBase::vftable (this node's base)
//      wh::xgenaimodule::BehaviorTree::C_InstantSendMessageToNPC::vftable (final)
//      wh::xgenaimodule::BehaviorTree::C_SendToNPC_Data::vftable (embedded member)
//
//    Constructors (all VERIFIED to build THIS class; named vftables visible):
//      sub_1806986D8  : full ctor. Stamps C_Node, then re-stamps the same
//                       subobject as C_SendMessageBase, then as
//                       C_InstantSendMessageToNPC; inits members; copies node-id.
//      sub_18138CB2C  : ctor variant (default-init, m_nodeId=0).
//      sub_1813925DC  : ctor that first builds C_SendMessageToNPC then re-stamps
//                       to C_InstantSendMessageToNPC (proves sibling kinship).
//      sub_180698598  : deleting destructor: frees 0x40 (sub_180834C6C(this,0x40)).
//
//    Concrete factory name string : 0x182aac8c0
//      ".?AVC_NodeFactory_InstantSendMessageToNPC@BehaviorTree@xgenaimodule@wh@@"
//    Templated factory-impl name  : 0x182aac700
//      C_NodeFactoryImpl<C_InstantSendMessageToNPC, C_InstantSendMessageToNPCContextCasting>
//    Factory registry record (VERIFIED) @ 0x182aac6c0:
//      { vtable, factoryObj, 0x29, xmlTag=0x182335228 }
//      ("InstantSendMessageToNPC" string is referenced only from here.)
//    Context pool name string : 0x182aac7b0
//      C_NodeContextPool<S_InstantSendMessageToNPCContext, C_InstantSendMessageToNPCContextCasting>
//    Per-entity context struct name string : 0x182aadf90
//      ".?AUS_InstantSendMessageToNPCContext@BehaviorTree@xgenaimodule@wh@@"
//    XML element-name string : 0x182335228  "InstantSendMessageToNPC"
//
//  VERIFIED INHERITANCE  (from ctor sub_1806986D8 re-stamp order)
//    I_NoRTTITypeInfo / I_DebugNode  (interface roots, obj +0x00 / +0x08)
//      <- C_Node               (I_Node interface base; vtable stamped first)
//        <- C_SendMessageBase  (re-stamped over the same subobject; this node's
//                               direct base, RTTI 0x182aade80)
//          <- C_InstantSendMessageToNPC  (final re-stamp; RTTI 0x182aaca20)
//    Plus an EMBEDDED MEMBER  C_SendToNPC_Data  at obj +0x38 (its own polymorphic
//    sub-object with vftables at +0x38 and +0x40 and a vbase-offset dword at +0x34).
//    This C_SendToNPC_Data member is the message-payload / dispatch helper that
//    actually carries the recipient + composed message.
//
//  VERIFIED OBJECT LAYOUT  (offsets from ctor sub_1806986D8; free size 0x40 for
//  the node proper, the C_SendToNPC_Data member extends the object past +0x40):
//    +0x00  void* vptr_INoRTTITypeInfo
//    +0x08  void* vptr_IDebugNode
//    +0x10  void* vptr_INode  (= C_SendMessageBase / C_InstantSendMessageToNPC
//                              final vtable 0x1821e7088)
//    +0x18  void* vptr_INode2 (second I_Node-interface slot, same final vtable)
//    +0x20  uint64_t m_field20 = 0          (ctor: =0)
//    +0x28  uint32_t m_nodeId               (ctor: =0, or copied from src+0x18)
//    +0x2C  uint32_t _pad2C
//    +0x30  uint64_t m_field30 = 0          (ctor: =0)
//    +0x34  int32_t  vbaseOff (C_SendToNPC_Data vbase-offset bookkeeping)
//    +0x38  C_SendToNPC_Data m_data         (embedded; vptr +0x38, vptr2 +0x40)
//
//  VERIFIED I_NODE VTABLE SLOTS (table 0x1821e7088; many entries are adjustor
//  thunks `target(this - *(int*)(this-4))`, confirming the multiple-inheritance
//  / vbase layout):
//    slot 0  sub_1803953E0 : return 0                        (type-info stub)
//    slot 1  sub_180B1B3F4 : thunk -> sub_180698598          (deleting dtor)
//    slot 2  sub_1803953E0 : return 0                        (Terminate stub)
//    slot 3  sub_1803AE988 : return *(GetCreator()+0x30)
//    slot 4  sub_1803AEAA4 : return *(GetFactory()+0x78)
//    slot 5  sub_180B1B680 : thunk -> sub_180698644          (Clone)
//    slot 6  sub_180B1B728 : thunk -> sub_1807021B0          (GetNodeCategory)
//    slot 7  sub_1806F99E0 : return *(uint*)(this+0x18)      (GetNodeId)
//    slot 8  sub_1807053B0 : *(uint*)(this+0x18) = arg        (SetNodeId)
//    slot 9  sub_180B1B780 : thunk -> sub_18064E540          (GetChildCount)
//    slot 10 sub_180434C90 : return 0                        (IsAction = false)
//    slot 14 sub_180B1B7BC : thunk -> sub_1813AD124          (OnInitialize)
//    slot 17 sub_181546330 : return (uint8)(status()-1) <= 2 (IsRunning-style)
//    (Interfuscator shuffles vtable order; semantic names are reliable only for
//     the content-matched slots above. GetNodeId at the I_Node-subobject's +0x18
//     corresponds to the most-derived object's m_nodeId at +0x28.)
//
//  VERIFIED XML -> C++ CHAIN
//    <InstantSendMessageToNPC> (tag 0x182335228, registry rec 0x182aac6c0)
//      -> C_NodeFactory_InstantSendMessageToNPC (0x182aac8c0)
//         == C_NodeFactoryImpl<C_InstantSendMessageToNPC,
//                              C_InstantSendMessageToNPCContextCasting> (0x182aac700)
//      -> node ctor (sub_1806986D8) -> object laid out as above
//      -> per-entity runtime data pooled by
//         C_NodeContextPool<S_InstantSendMessageToNPCContext, ...> (0x182aac7b0)
//
// ---------------------------------------------------------------------------
//  *** [UNVERIFIED] — NOT recovered this session ***
//   - C_SendToNPC_Data internal layout (its members hold the recipient + the
//     composed message). Only its embed offset (+0x38) and that it is
//     polymorphic are verified.
//   - The factory's NodeAttribute<T> bindings parsed from XML (message/mailbox
//     name, target selector, flags): names/types/offsets. The CreateNode/
//     LoadFromXml attribute path was not traced.
//   - Any E_SendMessageTarget enum (existence / enumerator names / values).
//   - The concrete engine "post message to mailbox" callee on send
//     (OnInitialize slot14 -> sub_180B1B7BC -> sub_1813AD124, body not traced
//     down to the mailbox dispatch).
//   - S_InstantSendMessageToNPCContext / S_SendMessageBaseContext member
//     layouts/sizes and the assumed S_BaseNodeContext root.
//   - C_SendMessageBase own members beyond being the node's direct base.
// ===========================================================================

namespace wh::xgenaimodule::BehaviorTree {

// ---------------------------------------------------------------------------
// C_SendToNPC_Data
//   Polymorphic data/dispatch sub-object embedded in the node at +0x38
//   (named vftable wh::xgenaimodule::BehaviorTree::C_SendToNPC_Data::vftable,
//    written by the node ctor at +0x38 and +0x40). Carries the resolved
//   recipient and the composed message and performs the actual mailbox post.
//   [UNVERIFIED] internal member layout and its own vtable methods.
// ---------------------------------------------------------------------------
class C_SendToNPC_Data {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_SendToNPC_Data;
    virtual ~C_SendToNPC_Data() = default;   // [UNVERIFIED] full vtable not mapped
    // [UNVERIFIED] members: recipient id + composed AI message + dispatch state.
};

// ---------------------------------------------------------------------------
// S_SendMessageBaseContext
//   RTTI: .?AUS_SendMessageBaseContext@BehaviorTree@xgenaimodule@wh@@ (0x182aad370)
//   [UNVERIFIED] Shared base of the SendMessage* family's per-entity runtime
//   context. Presumed to derive from S_BaseNodeContext (see C_NodeContext.h).
// ---------------------------------------------------------------------------
struct S_SendMessageBaseContext : S_BaseNodeContext /* [UNVERIFIED] base */ {
    inline static constexpr auto RTTI = Offsets::RTTI_S_SendMessageBaseContext;
    // [UNVERIFIED] members not recovered.
};

// ---------------------------------------------------------------------------
// S_InstantSendMessageToNPCContext
//   RTTI: .?AUS_InstantSendMessageToNPCContext@BehaviorTree@xgenaimodule@wh@@
//         (name string 0x182aadf90)
//   Per-entity heap runtime data, pooled by
//   C_NodeContextPool<S_InstantSendMessageToNPCContext,
//                     C_InstantSendMessageToNPCContextCasting> (0x182aac7b0).
//   Not stored in the node; reached via UpdateContext runtime-data pointer.
//   [UNVERIFIED] member layout/size.
// ---------------------------------------------------------------------------
struct S_InstantSendMessageToNPCContext : S_SendMessageBaseContext /* [UNVERIFIED] */ {
    inline static constexpr auto RTTI = Offsets::RTTI_S_InstantSendMessageToNPCContext;
    // [UNVERIFIED] no members confirmed.
};

// ---------------------------------------------------------------------------
// C_SendMessageBase
//   RTTI: .?AVC_SendMessageBase@BehaviorTree@xgenaimodule@wh@@ (0x182aade80)
//   VERIFIED direct base of C_InstantSendMessageToNPC (ctor re-stamps C_Node ->
//   C_SendMessageBase -> C_InstantSendMessageToNPC over the I_Node subobject).
//   Itself derives from C_Node (leaf: I_Node + I_DebugNode, integer node-id).
//   [UNVERIFIED] its own additional members.
// ---------------------------------------------------------------------------
class C_SendMessageBase : public C_Node {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_SendMessageBase;
    // [UNVERIFIED] family-shared parsed message attributes live here / in the
    // embedded C_SendToNPC_Data member of the derived node.
};

// ---------------------------------------------------------------------------
// C_InstantSendMessageToNPC
//   RTTI: .?AVC_InstantSendMessageToNPC@BehaviorTree@xgenaimodule@wh@@ (0x182aaca20)
//   Leaf node. Final vtable 0x1821e7088. Direct base C_SendMessageBase.
//   Object holds the C_Node/C_SendMessageBase portion (free size 0x40) plus an
//   embedded C_SendToNPC_Data member at +0x38.
// ---------------------------------------------------------------------------
class C_InstantSendMessageToNPC : public C_SendMessageBase {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_InstantSendMessageToNPC;
    using RuntimeData = S_InstantSendMessageToNPCContext;

    // ---- VERIFIED fields written by ctor sub_1806986D8 ----
    // (+0x00..+0x18 are the C_Node/C_SendMessageBase interface vptrs; +0x18
    //  carries the m_nodeId GetNodeId/SetNodeId read at +0x18 of that subobject,
    //  which is the most-derived +0x28.)
    uint64_t m_field20;        // +0x20  ctor: =0          [VERIFIED]
    uint32_t m_nodeId;         // +0x28  ctor: =0 / copied [VERIFIED] (GetNodeId/SetNodeId)
    uint32_t _pad2C;
    uint64_t m_field30;        // +0x30  ctor: =0          [VERIFIED]
    int32_t  m_dataVBaseOff;   // +0x34  C_SendToNPC_Data vbase-offset [VERIFIED present]
    C_SendToNPC_Data m_data;   // +0x38  embedded message/dispatch sub-object [VERIFIED location]

    // [UNVERIFIED] any further parsed-attribute fields after m_data; total size
    // not determined (node-proper portion frees 0x40, m_data extends it).

    // ---- behavior ----
    //   OnInitialize -> I_Node slot14 thunk sub_180B1B7BC -> sub_1813AD124:
    //     resolve target NPC, compose + post message via m_data; completes the
    //     same tick ("Instant"). [UNVERIFIED] dispatch callee body.
    //   GetNodeId/SetNodeId : verified slots 7/8.  Clone : verified slot 5.
};

// ---------------------------------------------------------------------------
// Sibling (NOT defined here): C_SendMessageToNPC (RTTI 0x182aac920, ctx
//   S_SendMessageToNPCContext 0x182aadff0) -- the non-instant variant, same
//   base/family; ctor sub_1813925DC proves the two are vtable-swap relatives.
//   Inferred difference: stays Running until send completes. [UNVERIFIED] diff.
// ---------------------------------------------------------------------------

}  // namespace wh::xgenaimodule::BehaviorTree
