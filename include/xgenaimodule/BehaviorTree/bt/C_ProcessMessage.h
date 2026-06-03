// ============================================================================
//  wh::xgenaimodule::BehaviorTree  —  C_ProcessMessage  (messaging system)
// ----------------------------------------------------------------------------
//  Behavior-tree node that waits for / receives a message from the running
//  entity's inbox (mailbox) and binds it into brain/context variables, e.g.:
//
//      <ProcessMessage variable="inbox" .../>
//
//  C_ProcessMessage is the STATELESS behaviour policy at the top of a 4-level
//  message-receive class family. The fully-spelled node type, taken VERBATIM
//  from the node constructor sub_18146A350 (and the RTTI name @ 0x182ad8680), is:
//
//      C_NodeWrapper< C_ProcessMessage,
//                     C_ReceiveMessageTimed< C_ProcessMessageBase >,
//                     S_ProcessMessageContext >
//
//  The structural-base chain (each link confirmed by its own RTTI name + the
//  C_NodeWrapper RTTI that names its TBase), bottom-up:
//
//      C_Decorator                              (1-child base, 0x30; C_Decorator.h)
//        └ C_ProcessMessageBase                 (name @ 0x182aceb70; wrapped as
//             C_NodeWrapper<C_ProcessMessageBase, C_Decorator,
//                           S_ProcessMessageBaseContext>  @ 0x182aced90)
//          └ C_ReceiveMessageBase<C_ProcessMessageBase>     (name @ 0x182acecb0)
//            └ C_ReceiveMessageTimed<C_ProcessMessageBase>  (name @ 0x182ad8440;
//                 wrapped as C_NodeWrapper<C_ReceiveMessageTimed<...>,
//                   C_ReceiveMessageBase<...>,
//                   S_ReceiveMessageTimedContext<S_ProcessMessageBaseContext>>
//                   @ 0x182ad84c0)
//              └ C_ProcessMessage  (this node's behaviour policy; name @ 0x182ad87c0)
//
//  i.e. the node is a single-child DECORATOR-based, TIMED message receiver. The
//  "Timed" layer adds a wait/timeout; the "ProcessMessage" policy maps the
//  received message onto context variables.
//
//  ───────────────  XML -> C++ -> engine call chain (VERIFIED)  ───────────────
//
//   Tables/.../*.xml   <ProcessMessage variable="..." .../>
//        |  BT loader resolves "ProcessMessage" -> its registered I_NodeFactory
//        |  singleton:
//        |    C_NodeFactoryImpl<C_ProcessMessage,
//        |        C_DefaultNodeContextCasting<S_ProcessMessageContext>>
//        |    RTTI name @ 0x182ad9030.
//        v
//   fac->CreateNode(nodeId, creator)            [sub_18142D848 @ 0x18142d848]:
//        size = fac->vfunc[+0x30]();            // GetContextSize()
//        record size at creator+0x48;           // sub_1805839DC
//        mem  = pooled_new(0x38);               // 0x38 == sizeof(node object)
//        node = sub_18142565C(mem);             // in-place node ctor; installs
//               C_NodeWrapper<C_ProcessMessage,...>::vftable @ 0x18248bfd4 into
//               node+0x00 (I_Node) and node+0x08 (I_DebugNode); a relocation
//               table (xmmword_1836FEA80) drives sub_18028F7CC to copy the parsed
//               variable-name handles into their node-relative slots.
//        node->vfunc[+0x120](creator);          // LoadFromXml-style descriptor bind
//        node->vfunc[+0x40](nodeId);            // SetNodeId  (C_Node::m_nodeId +0x18)
//        return node;
//        (creator is stored at node+0x20 == C_Node::m_pCreator on the 0x28 path;
//         this node uses the 0x38 path which adds child + receive-base fields.)
//        v
//   Per ENTITY/instance: the factory's C_NodeContextPool<S_ProcessMessageContext>
//   (RTTI name @ 0x182ad8f50) allocates one S_ProcessMessageContext (0x78 bytes,
//   built by the base ctor sub_1812EE27C which installs S_BaseNodeContext::vftable
//   and whose scalar-deleting variant frees 0x78). All MUTABLE per-tick state
//   lives here; the node object is stateless and shared (see C_NodeWrapper.h).
//        v
//   Per tick (node primary I_Node vtable @ 0x1821f2148, policy-typed view; the
//   wrapper-typed view is @ 0x18248bfd4 — same functions):
//     OnInitialize [slot 14, sub_18148025C @ 0x18148025c]:
//        for each entry in three field-binding tables (xmmword_1836FEA80 /
//        ..A98 / ..AB0): resolve the bound message-field name (sub_18147961C),
//        if the live message HAS it (msg->vfunc[+0xF0]) read it
//        (msg->vfunc[+0xE8]), StringHash it, and store the resulting
//        ref-counted-string handle into the node/child slot at the table offset.
//        => binds the XML "variable" + message attributes to brain variables.
//     OnTerminate [slot 15, sub_18148C0A4 @ 0x18148c0a4]:
//        symmetric: re-publishes / releases each bound field back through the
//        same tables, then sub_18148A2EC finalises.
//     Update [slot 17, sub_181546330 @ 0x181546330]:
//        st = self->vfunc[+0x80]();             // base "receive" tick
//        return (uint8)(st - 1) <= 2;           // Running(2)/Suspended(3)... -> true
//                                               // i.e. still active vs done.
//     LoadFromXml [slot 27, sub_18057FD34 @ 0x18057fd34]:
//        generic decorator load: marks loading, calls self->vfunc[+0x1C0](xml)
//        (the per-policy attribute bind), then loads/【attaches the single child.
//
//  ── Evidence (WHGame.dll, imagebase 0x180000000) — ALL VERIFIED ────────────
//
//   RTTI name strings (idautils.Strings; each returned in full):
//     C_ProcessMessage                              @ 0x182ad87c0
//        ".?AVC_ProcessMessage@BehaviorTree@xgenaimodule@wh@@"
//     C_ProcessMessageBase                          @ 0x182aceb70
//     C_ReceiveMessageBase<C_ProcessMessageBase>    @ 0x182acecb0
//     C_ReceiveMessageTimed<C_ProcessMessageBase>   @ 0x182ad8440
//     C_NodeWrapper<C_ProcessMessage,
//        C_ReceiveMessageTimed<C_ProcessMessageBase>,
//        S_ProcessMessageContext>  (the node type) @ 0x182ad8680
//        primary vtable @ 0x18248bfd4 (ctors sub_18146A350 @0x18146a350,
//        sub_181484F40, sub_181485640); secondary I_DebugNode vt @ 0x18248bfac.
//     S_ProcessMessageContext (struct)              @ 0x182ad8770
//     C_NodeContextPool<S_ProcessMessageContext,...> @ 0x182ad8f50
//     C_NodeFactoryImpl<C_ProcessMessage,...>       @ 0x182ad9030
//
//   ProcessMessage policy-typed node vtables (td @ 0x182ad87b0; COLs in .rdata
//   0x182441bc8 off0, 0x182441bf0 off8, 0x182554644 off0):
//     primary  I_Node     @ 0x1821f2148 (64 slots, all valid .text, dumped)
//     secondary I_DebugNode @ 0x1821f2110 (6 slots)
//   Node ctors that name the wrapper verbatim: sub_1806B7E70 @ 0x1806b7e70
//   (pooled-alloc path via sub_1806B7DF8), sub_18146A720 @ 0x18146a720,
//   sub_181425DAC (in-place via the factory).
//
//   Node-object size: 0x38 (factory CreateNode sub_18142D848 allocates 0x38; the
//   simpler leaf path sub_18142EF9C allocates 0x28 and sets creator@+0x20 /
//   nodeId@+0x18). VERIFIED.
//
//   S_ProcessMessageContext: built by the base context ctor sub_1812EE27C
//   (installs S_BaseNodeContext::vftable; scalar-deleting frees 0x78) => sizeof
//   == 0x78. The context's own derived members are NOT initialised by that base
//   ctor; they are populated per-tick by OnInitialize (sub_18148025C) through the
//   field-binding tables. [UNVERIFIED] exact per-field offsets inside the context.
//
//  ── CORRECTION (supersedes an earlier draft) ───────────────────────────────
//  An earlier draft of this file attributed sub_1808A3B10 (+0x18/+0x38/+0x54/
//  +0x58/+0x5F/+0x60..+0x70 writes) to this node and claimed a "transport fault".
//  That was WRONG: sub_1808A3B10 / sub_1808A3A40 are unrelated bitstream/anim-
//  track serialization routines (they read floats via sub_180916160) and are
//  reached only by DATA refs from 0x182287cf0 / 0x18382c124, NOT by any
//  C_ProcessMessage ctor. This file is built from the verified RTTI chain, the
//  actual node ctors, the factory CreateNode, and the decompiled behaviour slots.
// ============================================================================
#pragma once
#include <cstdint>
#include "../I_Node.h"
#include "../C_Node.h"          // C_Node leaf header (m_nodeId +0x18, m_pCreator +0x20)
#include "../C_Decorator.h"     // C_Decorator (1-child base, 0x30) — base of this family
#include "../C_NodeWrapper.h"   // C_NodeWrapper<TNode, TBase, TContext>
#include "../C_NodeContext.h"   // S_BaseNodeContext, C_DefaultNodeContextCasting, C_NodeContextPool
#include "../C_NodeFactory.h"   // I_NodeFactory, C_NodeFactoryImpl<TNode, TCasting>

namespace wh { namespace xgenaimodule { namespace BehaviorTree {

// ----------------------------------------------------------------------------
// Per-context-layer runtime structs (heap, owned by the node's context pool).
// These mirror the C_NodeWrapper TContext template args spelled out in the RTTI:
//   C_NodeWrapper<C_ProcessMessageBase, C_Decorator, S_ProcessMessageBaseContext>
//   C_NodeWrapper<C_ReceiveMessageTimed<..>, C_ReceiveMessageBase<..>,
//                 S_ReceiveMessageTimedContext<S_ProcessMessageBaseContext>>
//   C_NodeWrapper<C_ProcessMessage, C_ReceiveMessageTimed<..>,
//                 S_ProcessMessageContext>
// Each derives (in source) from S_BaseNodeContext; total sizeof == 0x78 (the
// base ctor sub_1812EE27C frees 0x78). [UNVERIFIED] the individual member
// offsets within each layer — only the total stride is pinned.
// ----------------------------------------------------------------------------

// Base per-node-instance context for the C_ProcessMessageBase decorator layer.
struct S_ProcessMessageBaseContext : public S_BaseNodeContext
{
    // [UNVERIFIED] members (decorator + message-base per-tick state).
};

// Timed-receive context layer; the RTTI shows it is templated on the inner
// (process-message-base) context:  S_ReceiveMessageTimedContext<TInner>.
template <typename TInner = S_ProcessMessageBaseContext>
struct S_ReceiveMessageTimedContext : public TInner
{
    // [UNVERIFIED] members (timeout / deadline / pending-message state).
};

// ----------------------------------------------------------------------------
// S_ProcessMessageContext
//   RTTI: .?AUS_ProcessMessageContext@BehaviorTree@xgenaimodule@wh@@ (struct;
//         name @ 0x182ad8770). Top per-instance context for the ProcessMessage
//         node. Owned by C_NodeContextPool<S_ProcessMessageContext,
//         C_DefaultNodeContextCasting<S_ProcessMessageContext>> (name @
//         0x182ad8f50). Built by the base context ctor sub_1812EE27C (installs
//         S_BaseNodeContext::vftable; scalar-deleting frees 0x78) => sizeof 0x78.
//
//   Holds the bound message-field handles (ref-counted-string / StringHash
//   handles) that OnInitialize (sub_18148025C) writes from the live inbox
//   message, plus the timed-receive runtime state inherited from the layers
//   above. [UNVERIFIED] exact member offsets (only total size 0x78 is pinned;
//   the per-field offsets live in the relocation tables xmmword_1836FEA80 /
//   ..A98 / ..AB0 consumed by OnInitialize/OnTerminate).
// ----------------------------------------------------------------------------
struct S_ProcessMessageContext
    : public S_ReceiveMessageTimedContext<S_ProcessMessageBaseContext>
{
    // [UNVERIFIED] members. Total sizeof == 0x78 (VERIFIED via sub_1812EE27C).
    // Per-field bindings (the XML "variable" target + message attributes) are
    // resolved at runtime through the field-binding tables, not via fixed
    // members visible at this layer.
};

// ----------------------------------------------------------------------------
// C_ProcessMessageBase  (structural base of the message-receive family)
//   RTTI: .?AVC_ProcessMessageBase@BehaviorTree@xgenaimodule@wh@@ (name @
//         0x182aceb70). Wrapped as C_NodeWrapper<C_ProcessMessageBase,
//         C_Decorator, S_ProcessMessageBaseContext> (name @ 0x182aced90) => its
//         structural base is C_Decorator (single child, 0x30). VERIFIED.
//   [UNVERIFIED] node-side data members beyond the C_Decorator header.
// ----------------------------------------------------------------------------
class C_ProcessMessageBase : public C_Decorator {
    // [UNVERIFIED] extra members (message-routing ids/handles placed by the
    // node ctor's relocation-table fixup loop; offsets not individually pinned).
};

// ----------------------------------------------------------------------------
// C_ReceiveMessageBase<TBase>  (name @ 0x182acecb0)
//   Adds the basic "receive a message" control flow over a message base.
//   For this node, TBase = C_ProcessMessageBase.
// ----------------------------------------------------------------------------
template <typename TBase = C_ProcessMessageBase>
class C_ReceiveMessageBase : public TBase {
    // [UNVERIFIED] members (subscription / pending-message handle).
};

// ----------------------------------------------------------------------------
// C_ReceiveMessageTimed<TBase>  (name @ 0x182ad8440)
//   Adds a timed (wait-with-timeout) receive. It is the TBase of the
//   C_ProcessMessage wrapper. RTTI shows it derives from
//   C_ReceiveMessageBase<TBase>. For this node, TBase = C_ProcessMessageBase.
// ----------------------------------------------------------------------------
template <typename TBase = C_ProcessMessageBase>
class C_ReceiveMessageTimed : public C_ReceiveMessageBase<TBase> {
    // [UNVERIFIED] members (timeout / deadline field).
};

// ----------------------------------------------------------------------------
// C_ProcessMessage  (stateless node behaviour policy)
//   RTTI: .?AVC_ProcessMessage@BehaviorTree@xgenaimodule@wh@@
//         (name @ 0x182ad87c0; type descriptor @ 0x182ad87b0)
//
//   Receives a message from the entity inbox and binds its fields onto the bound
//   brain/context variable(s) (the XML "variable" attribute, e.g. "inbox").
//
//   Stateless TNode policy folded into
//       C_NodeWrapper<C_ProcessMessage,
//                     C_ReceiveMessageTimed<C_ProcessMessageBase>,
//                     S_ProcessMessageContext>.
//   Has NO data members of its own; all state is in S_ProcessMessageContext and
//   the C_ReceiveMessageTimed base. The methods below are the verified bodies the
//   wrapper's vtable slots delegate to (node vtable @ 0x1821f2148 / 0x18248bfd4).
// ----------------------------------------------------------------------------
class C_ProcessMessage
{
public:
    using RuntimeData = S_ProcessMessageContext;

    // [14] sub_18148025C: bind each subscribed message field from the live inbox
    //      message into the node/child slots (StringHash handles).
    bool          OnInitialize(RuntimeData& ctx);
    // [15] sub_18148C0A4: re-publish / release each bound field, then finalise.
    bool          OnTerminate (RuntimeData& ctx);
    // [17] sub_181546330: tick the timed receive; returns "still active" while
    //      the base status is in the Running/Suspended band, else completes.
    bool          Update      (RuntimeData& ctx);
    // [27] sub_18057FD34: decorator-style load — bind policy attributes, then the
    //      single child.
    bool          LoadFromXml (void* xmlNode, void* loadCtx);

    // No data members (stateless policy).
};

// ----------------------------------------------------------------------------
// Concrete node + factory + pool aliases (all template args VERIFIED from RTTI).
// ----------------------------------------------------------------------------
using C_ProcessMessageNode =
    C_NodeWrapper<C_ProcessMessage,
                  C_ReceiveMessageTimed<C_ProcessMessageBase>,
                  S_ProcessMessageContext>;                         // node @ vt 0x18248bfd4

using C_ProcessMessageFactory =
    C_NodeFactoryImpl<C_ProcessMessage,
                      C_DefaultNodeContextCasting<S_ProcessMessageContext> >; // @ 0x182ad9030

using C_ProcessMessageContextPool =
    C_NodeContextPool<S_ProcessMessageContext,
                      C_DefaultNodeContextCasting<S_ProcessMessageContext> >; // @ 0x182ad8f50

// ============================================================================
//  [UNVERIFIED] — not pinned to a single concrete value:
//   1. Individual data-member offsets inside S_ProcessMessageContext and the
//      intermediate context layers (S_ProcessMessageBaseContext,
//      S_ReceiveMessageTimedContext). Only the TOTAL context size 0x78 is pinned
//      (base ctor sub_1812EE27C scalar-deleting frees 0x78). The per-field
//      bindings are runtime-table-driven (xmmword_1836FEA80/..A98/..AB0), not
//      fixed struct members at this layer.
//   2. Node-side data members of C_ProcessMessageBase / C_ReceiveMessageBase /
//      C_ReceiveMessageTimed beyond the C_Decorator header. The node object is
//      0x38 bytes (VERIFIED via factory CreateNode sub_18142D848 alloc 0x38);
//      the +0x28..+0x37 region holds the decorator child pointer + receive-base
//      fields placed by the node ctor's relocation-table fixup loop, but the
//      exact field meanings were not individually decompiled.
//   3. The "Timed" base's timeout/deadline field location.
//   4. Per-slot ordering of the full 64-slot primary vtable: every entry is a
//      valid .text function (dumped & validated) but only behaviour slots
//      14/15/17/27/39 were decompiled to confirm their roles.
//   5. NOTE: the IDA-MCP result transport intermittently returned empty payloads
//      / syntax-echo errors during this session; every fact above comes from a
//      tool result that returned in full and was re-confirmed.
// ============================================================================

}}} // namespace wh::xgenaimodule::BehaviorTree
