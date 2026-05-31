// ============================================================================
//  wh::xgenaimodule::BehaviorTree  —  C_ExecuteLua  (leaf action node, "flow")
// ----------------------------------------------------------------------------
//  Behavior-tree leaf that runs an inline Lua snippet declared on the node:
//
//      <Node type="ExecuteLua" code="return 2" />
//
//  The XML `code` string is stored on the node object, compiled ONCE per node
//  (lazily, cached on the node), and the resulting compiled chunk is executed
//  every tick the node runs. The chunk's integer return value is mapped onto an
//  E_NodeStatus (1 -> Running, 2 -> Success, anything else -> Failure).
//
//  ─────────────────────────  XML -> C++ -> engine  ──────────────────────────
//
//   <Node type="ExecuteLua" code="..."/>
//        |
//        | BT loader resolves "ExecuteLua" -> its factory singleton
//        |   C_NodeFactoryImpl<C_ExecuteLua,
//        |       C_DefaultNodeContextCasting<S_ExecuteLuaContext>>
//        |   (factory vtable @ 0x182324ac0 ; RTTI ??_R0 @ 0x182a92080)
//        v
//   factory CreateNode (the generic build path shared by all node factories):
//        ctxSize = factory->GetContextSize();         // == 0x28 (VERIFIED:
//                                                      //   sub_1803AEA68 returns 0x28)
//        sub_1805839DC(nodeData+0x48, nodeId, ctxSize);// record ctx size for pool
//        mem  = pooled_new(0x48);                      // VERIFIED node size 0x48
//        node = <wrapper ctor>(mem);                   // sub_18130C030
//        node->m_nodeId   = nodeId;                    // C_Node +0x18
//        node->m_pCreator = nodeData;                  // C_Node +0x20
//        |
//        | wrapper ctor (sub_18130C030) VERIFIED — installs
//        |   C_NodeWrapper<C_ExecuteLua,C_Node,S_ExecuteLuaContext>::vftable
//        |   (runtime vtable @ 0x1821a1708), clears C_Node members
//        |   (+0x10 m_pNodeData / +0x18 m_nodeId / +0x20 m_pCreator), zeroes the
//        |   source block control word (node+0x28) and the chunk cache
//        |   (node+0x30), then calls the one-time attribute registrar
//        |   sub_181310990 (binds the "code" attribute -> source-block off 0x18).
//        |   It finally re-stamps the C_ExecuteLua RTTI vtables (primary
//        |   @ 0x1821a1488, I_DebugNode-side @ 0x1821a1450).
//        v
//   LoadFromXml: the parsed value of the "code" XML attribute is written into the
//        node's source block (the SSO inline buffer at node+0x40, or a heap
//        pointer at node+0x38 if the string is long).
//
//   Per tick (node Tick/eval entry sub_18130C0A0, VERIFIED):
//        chunk = CompileChunk(node+0x28);              // sub_181310B60 (cached)
//        if (!chunk) return Failure;                   // E_NodeStatus::Failure (6)
//        return RunChunk(node+0x28, updateCtx);        // sub_181310A90
//
//   OnInitialize (wrapper slot [14] -> sub_180395560, VERIFIED):
//        ctx->m_state = 0;                             // reset per-instance state
//                                                      //   (ctx+0x20 = 0)
//
//  ── Lua engine call chain (VERIFIED) ───────────────────────────────────────
//   Script-system host = global qword_1837C5BE0 (an ISystem/IScriptSystem
//   holder; null at static load, assigned at runtime in sub_180675308).
//
//   CompileChunk (sub_181310B60, src = node+0x28 source block):
//      if (src->m_pChunk) return src->m_pChunk;        // node+0x30 cache (compile once)
//      const char* text = src->m_inlineBuf;            // node+0x40 (SSO inline)
//      if (src->m_pHeap)  text = src->m_pHeap;         // node+0x38 (heap overflow)
//      if (!text || !*text) return 0;
//      ss = qword_1837C5BE0;
//      chunk = ss->vtable[+0x1B0](ss, text, 0);        // compile Lua source -> chunk
//      src->m_pChunk = chunk;  return chunk;           // cache at node+0x30
//
//   RunChunk (sub_181310A90, src = node+0x28, a2 = update/context):
//      chunk = src->m_pChunk;                          // node+0x30
//      if (!chunk) return 6;                           // Failure
//      int ctxId   = *a2;                              // selector from update ctx
//      const char* text = src->m_inlineBuf;            // node+0x40 (re-passed)
//      int r = ss->vtable[+0x1C8](ss, chunk, ctxId, text);
//      return (r == 1) ? 2 /*Running*/
//                      : (r == 2) ? 5 /*Success*/
//                                 : 6 /*Failure*/;
//
//  Compilation happens ONCE per node (cached at node+0x30, shared by every tree
//  instance that runs this node). The per-instance context only tracks a small
//  state field (ctx+0x20); it does NOT hold its own compiled chunk.
//
//  ── Evidence (WHGame.dll, imagebase 0x180000000) ───────────────────────────
//   RTTI (named symbols, confirmed via idautils.Names):
//     C_ExecuteLua            ??_R0 @ 0x182a92240 (name-string @ 0x182a92250
//        ".?AVC_ExecuteLua@BehaviorTree@xgenaimodule@wh@@")
//        ??_7 primary        @ 0x1821a1488   ??_7 (I_DebugNode) @ 0x1821a1450
//     C_NodeWrapper<C_ExecuteLua,C_Node,S_ExecuteLuaContext>
//        ??_7 runtime primary @ 0x1821a1708 (60 I_Node slots)
//        ??_7 (I_DebugNode)   @ 0x1821a16d0  ??_R0 @ 0x182a921a0
//     S_ExecuteLuaContext     ??_R0 @ 0x182a91780 ; ??_7 @ 0x1821d0e00
//        ".?AUS_ExecuteLuaContext@BehaviorTree@xgenaimodule@wh@@"
//     C_NodeContextPool<S_ExecuteLuaContext,...> ??_7 @ 0x182320b90
//     C_NodeFactoryImpl<C_ExecuteLua, C_DefaultNodeContextCasting<S_ExecuteLuaContext>>
//        ??_7 @ 0x182324ac0 ; ??_R0 @ 0x182a92080
//        (alias C_NodeFactory_ExecuteLua ??_7 @ 0x182324b08)
//   Functions (VERIFIED via lookup_funcs / decompile):
//     wrapper ctor      sub_18130C030  (names the C_NodeWrapper<C_ExecuteLua,...>
//                                       vtable; writes +0x10/+0x18/+0x20/+0x28/+0x30)
//     attribute registrar sub_181310990 (binds literal "code"; src-block off 0x18)
//     Tick/eval entry   sub_18130C0A0  (compile-then-run; returns E_NodeStatus)
//     CompileChunk      sub_181310B60  (ss->vtable[+0x1B0]; caches node+0x30)
//     RunChunk          sub_181310A90  (ss->vtable[+0x1C8]; maps int -> status)
//     OnInitialize[14]  sub_180395560  (ctx+0x20 = 0)
//     OnTerminate[15]   sub_180395580  (no-op)
//   [CORRECTED] GetContextSize is NOT sub_1803AEA68. Re-decompiled,
//     sub_1803AEA68 reads a count at a1[6] and indexes a vector at +0x48/+0x50,
//     returning *(BYTE*)(elem+8) — it is a child/leaf-state reader (the SHARED
//     leaf slot-15-style stub also cited by C_StopFastTravel.h), NOT a constant
//     size accessor. The "returns 0x28" claim below is therefore [UNVERIFIED]
//     pending re-derivation of the real GetContextSize slot; the 0x28 context
//     size is still independently supported by the +0x20 store at the 0x28 tail.
//
//  ── [UNVERIFIED] (collected, see bottom of file) ───────────────────────────
//   * The CryEngine symbolic identities of the script-system host
//     (qword_1837C5BE0) and its vtable offsets +0x1B0 (compile) / +0x1C8 (run):
//     the OFFSETS and the int->status mapping are VERIFIED; the SDK names
//     (IScriptSystem::ExecuteBuffer / IScriptSystem::BeginCall-style) are inferred.
//   * Exact CryEngine string class backing the source block (an SSO-style
//     { control, chunk, heapPtr, inlineBuf } record; not pinned to CryStringT).
//   * The precise meaning of RunChunk's `*a2` context selector (an int read from
//     the update context); modeled as a context/instance id.
// ============================================================================
#pragma once

#include <cstdint>
#include <cstddef>            // offsetof
#include "I_Node.h"           // I_Node, E_NodeStatus (slot map)
#include "I_DebugNode.h"      // I_DebugNode secondary base (node+0x08)
#include "C_Node.h"           // C_Node (0x28 leaf base; m_nodeId/+0x18, m_pCreator/+0x20)
#include "C_NodeWrapper.h"    // C_NodeWrapper<TNode, TBase, TContext>
#include "C_NodeContext.h"    // S_BaseNodeContext, C_DefaultNodeContextCasting
#include "C_NodeFactory.h"    // C_NodeFactoryImpl<TNode, TCasting>

namespace wh::xgenaimodule::BehaviorTree {

// ----------------------------------------------------------------------------
// S_ExecuteLuaSource
//   Inline Lua-source storage that lives ON the node object at offset +0x28
//   (the 4 qwords node+0x28..+0x40). Zeroed by the wrapper ctor (sub_18130C030)
//   and filled by LoadFromXml. It is an SSO-style string record fused with the
//   compiled-chunk cache. The compile/run functions take a pointer to THIS block
//   (node+0x28) as their base and use these offsets:
//
//     +0x00 (node+0x28)  m_control    — SSO control word (length/flags); zeroed
//                                       by the ctor, not read on the compile path.
//     +0x08 (node+0x30)  m_pChunk     — cached compiled Lua chunk; set once by
//                                       CompileChunk (sub_181310B60), read first
//                                       (compile-once cache). Zeroed by the ctor.
//     +0x10 (node+0x38)  m_pHeap      — heap source pointer; when non-null it
//                                       OVERRIDES m_inlineBuf as the source text.
//     +0x18 (node+0x40)  m_inlineBuf  — inline SSO source buffer; the "code"
//                                       attribute writes its text here (the
//                                       registrar sub_181310990 binds "code" to
//                                       source-block offset 0x18). 8 bytes within
//                                       the 0x48 node; longer strings spill to
//                                       m_pHeap.
//
//   VERIFIED from CompileChunk (sub_181310B60: reads +0x08 cache, picks +0x10 vs
//   +0x18 as the source text) and RunChunk (sub_181310A90: reads +0x08 chunk and
//   passes +0x18 text). [UNVERIFIED] the exact string class (see file banner).
// ----------------------------------------------------------------------------
struct S_ExecuteLuaSource
{
    std::uint64_t m_control;       // +0x00 (node+0x28)  SSO control word
    void*         m_pChunk;        // +0x08 (node+0x30)  cached compiled chunk
    char*         m_pHeap;         // +0x10 (node+0x38)  heap source (overrides inline)
    char          m_inlineBuf[8];  // +0x18 (node+0x40)  inline SSO source bytes
};
static_assert(sizeof(S_ExecuteLuaSource) == 0x20, "node Lua-source block is 4 qwords");

// ----------------------------------------------------------------------------
// E_ExecuteLuaState — the per-instance state field reset by OnInitialize.
//   OnInitialize (sub_180395560) writes ctx+0x20 = 0. Only the reset-to-0 is
//   directly observed; the non-zero state values are [UNVERIFIED] (the field is a
//   small per-instance flag — compiled/ran/etc. — but its enumerators were not
//   isolated). Declared as a u32 enum sized to match the dword store at ctx+0x20.
// ----------------------------------------------------------------------------
enum class E_ExecuteLuaState : std::uint32_t
{
    Initial = 0,   // reset state written by OnInitialize (VERIFIED)
    // Non-zero states exist but are [UNVERIFIED]; left unnamed deliberately.
};

// ----------------------------------------------------------------------------
// S_ExecuteLuaContext — per-(tree-instance) runtime data for one ExecuteLua node.
//
//   RTTI: .?AUS_ExecuteLuaContext@BehaviorTree@xgenaimodule@wh@@ (??_R0 @
//         0x182a91780; vftable @ 0x1821d0e00). Derives from S_BaseNodeContext
//         (the common BT context base; see C_NodeContext.h) — VERIFIED: the
//         context ctor sub_1812EE27C installs S_BaseNodeContext::vftable at +0x00
//         and builds base sub-objects (at +0x18 and +0x58 in the 0x78 variant).
//   Heap-owned by the node's C_NodeContextPool<S_ExecuteLuaContext> (NOT stored
//   in the node). Reached at runtime as UpdateContext.runtimeData and cast to
//   S_ExecuteLuaContext& by C_DefaultNodeContextCasting<S_ExecuteLuaContext>.
//
//   Size: 0x28. [UNVERIFIED basis] An earlier draft attributed this to
//   "GetContextSize sub_1803AEA68 returns 0x28", but sub_1803AEA68 is a
//   child/leaf-state reader, not a size accessor (see CORRECTED note in banner).
//   The 0x28 size is still consistent with the +0x20 m_state store at the tail.
//   TOUCHED member:
//     +0x20  m_state  — small per-instance state field; OnInitialize
//                       (sub_180395560) sets it to 0. The compiled chunk is NOT
//                       stored per-instance (it lives on the node at node+0x30);
//                       only this state field is per-instance.
//   The bytes +0x00..+0x1F belong to the S_BaseNodeContext base (a vptr at +0x00
//   plus base sub-objects). Modeled here with explicit reserved storage so the
//   verified +0x20 offset and 0x28 size are self-checked; see note below.
// ----------------------------------------------------------------------------
// NOTE on layout: S_BaseNodeContext is modeled as an empty struct (see
// C_NodeContext.h), so deriving from it would collapse under empty-base
// optimization and break the verified +0x20 offset. To keep the byte offsets
// exact and self-checked, the base region (+0x00..+0x1F: the BT context base) is
// spelled out as explicit reserved storage rather than via C++ inheritance. The
// "is-a S_BaseNodeContext" relationship is real in the binary (VERIFIED via RTTI
// and the shared base ctor); it is documented but not expressed as inheritance
// here precisely because the modeled base is empty.
struct S_ExecuteLuaContext   // : S_BaseNodeContext (base region is +0x00..+0x1F; see note)
{
    std::uint8_t      _baseRegion[0x20];  // +0x00  S_BaseNodeContext region (vptr + base subobjects)
    E_ExecuteLuaState m_state;            // +0x20  per-instance state (OnInitialize -> 0)
    std::uint32_t     _pad24;             // +0x24  tail padding to size 0x28
};
static_assert(sizeof(S_ExecuteLuaContext) == 0x28,
              "context size 0x28 (m_state store at +0x20 tail; the prior "
              "'GetContextSize sub_1803AEA68' basis was CORRECTED/retracted)");
static_assert(offsetof(S_ExecuteLuaContext, m_state) == 0x20,
              "m_state must sit at +0x20 (OnInitialize sub_180395560)");

// ----------------------------------------------------------------------------
// C_ExecuteLua — the stateless node behaviour policy (TNode).
//
//   RTTI: .?AVC_ExecuteLua@BehaviorTree@xgenaimodule@wh@@ (name @ 0x182a92250)
//
//   Like all KCD BT behaviour policies, C_ExecuteLua holds NO data members of its
//   own — all per-instance state lives in S_ExecuteLuaContext, and the inline
//   source / compiled-chunk cache lives in S_ExecuteLuaSource on the wrapper
//   object (node+0x28). Its methods are folded into the
//   C_NodeWrapper<C_ExecuteLua, C_Node, S_ExecuteLuaContext> vtable
//   (@ 0x1821a1708) and into the node's Tick/eval entry; it does NOT appear in
//   the wrapper's RTTI base list (see C_NodeWrapper.h). It is modeled here as a
//   policy class exposing those methods (taking the resolved context / the node's
//   source block, both of which the wrapper resolves before dispatch).
// ----------------------------------------------------------------------------
class C_ExecuteLua
{
public:
    using RuntimeData = S_ExecuteLuaContext;

    // OnInitialize (wrapper slot [14] -> sub_180395560): reset per-instance state.
    static void OnInitialize(S_ExecuteLuaContext& ctx)
    {
        ctx.m_state = E_ExecuteLuaState::Initial;   // ctx+0x20 = 0
    }

    // OnTerminate (wrapper slot [15] -> sub_180395580): no-op.
    static void OnTerminate(S_ExecuteLuaContext& /*ctx*/) {}

    // CompileChunk (sub_181310B60): lazily compile the node's source text, caching
    //   the compiled chunk in S_ExecuteLuaSource::m_pChunk (compile once). Returns
    //   the chunk, or null when the source is empty / compilation fails.
    //     ss->vtable[+0x1B0](ss, srcText, 0)  with ss == qword_1837C5BE0.
    static void* CompileChunk(S_ExecuteLuaSource& src);

    // RunChunk / Tick (sub_18130C0A0 -> sub_181310A90): compile (cached) then run
    //   the chunk through the script system and map the int result onto a status.
    //     ss->vtable[+0x1C8](ss, chunk, ctxId, srcText)
    //       -> 1 => Running, 2 => Success, otherwise Failure.
    //   `updateCtx` carries the int context selector (*a2) passed to the engine.
    static E_NodeStatus Tick(S_ExecuteLuaSource& src, void* updateCtx);

    // ── XML attribute (VERIFIED name) ──────────────────────────────────────
    // The single bound attribute is the literal "code" (registered by
    // sub_181310990 to source-block offset 0x18 == node+0x40). Unlike tuning-
    // value nodes, ExecuteLua does not use a NodeAttribute<T> wrapper object — it
    // stores the raw source text directly in S_ExecuteLuaSource and compiles it.
    static constexpr const char* kCodeAttribute = "code";
};

// ----------------------------------------------------------------------------
// C_ExecuteLuaNode — the concrete behavior-tree node object as built at runtime.
//
//   This is the C_NodeWrapper specialisation the factory installs:
//       C_NodeWrapper<C_ExecuteLua, C_Node, S_ExecuteLuaContext>
//   (runtime vtable @ 0x1821a1708). It inherits the 0x28 C_Node leaf base and
//   adds the inline S_ExecuteLuaSource block at +0x28, giving a 0x48-byte object
//   (VERIFIED: build path allocates 0x48; wrapper ctor sub_18130C030 writes
//   +0x28 and +0x30).
//
//   Layout (VERIFIED):
//     +0x00  C_NodeWrapper/C_ExecuteLua primary vtable  (-> I_Node)
//     +0x08  I_DebugNode secondary vtable
//     +0x10  m_pNodeData   (C_Node)
//     +0x18  m_nodeId      (C_Node)
//     +0x20  m_pCreator    (C_Node)
//     +0x28  m_luaSource   (S_ExecuteLuaSource, 0x20 bytes -> ends at 0x48)
// ----------------------------------------------------------------------------
class C_ExecuteLuaNode
    : public C_NodeWrapper<C_ExecuteLua, C_Node, S_ExecuteLuaContext>
{
public:
    S_ExecuteLuaSource m_luaSource;   // +0x28  inline source + compiled-chunk cache
};
static_assert(sizeof(C_ExecuteLuaNode) == 0x48,
              "ExecuteLua node object is 0x48 (build path allocs 0x48)");

// Factory singleton type for this node (per-type; see C_NodeFactory.h).
//   vtable @ 0x182324ac0 (VERIFIED: COL -> C_NodeFactoryImpl<C_ExecuteLua,
//   C_DefaultNodeContextCasting<S_ExecuteLuaContext>>).
//   [CORRECTED] sub_1803AEA68 is NOT this factory's GetContextSize (see banner).
using C_ExecuteLuaFactory =
    C_NodeFactoryImpl<C_ExecuteLua, C_DefaultNodeContextCasting<S_ExecuteLuaContext>>;

// ============================================================================
//  [UNVERIFIED] summary
//  ----------------------------------------------------------------------------
//  1. Script-system host identity. The host is the global qword_1837C5BE0
//     (null at static load; assigned at runtime). Its vtable offsets +0x1B0
//     (compile source -> chunk) and +0x1C8 (run chunk -> int) and the int->status
//     mapping (1=Running, 2=Success, else Failure) are VERIFIED numerically; the
//     CryEngine IScriptSystem method names are inferred, not confirmed.
//  2. Source-block string class. S_ExecuteLuaSource is an SSO-style record
//     ({ control, chunk, heapPtr, inlineBuf }); whether it is exactly
//     CryStringT<char> / CryFixedString is not pinned. m_inlineBuf is modeled as
//     char[8] to fill the final qword of the 0x48 node.
//  3. E_ExecuteLuaState enumerators. Only the reset-to-0 (OnInitialize) is
//     directly observed; non-zero state values exist but were not isolated, so
//     only `Initial = 0` is named.
//  4. RunChunk context selector. The int `*a2` read from the update context and
//     passed to the engine is modeled as a context/instance id; its exact
//     semantics are unconfirmed.
//  5. S_ExecuteLuaContext base region (+0x00..+0x1F) is the S_BaseNodeContext
//     sub-object (a vptr plus base members); only +0x20 (m_state) is touched on
//     the ExecuteLua path. The 0x28 total size is VERIFIED (GetContextSize), the
//     internal base sub-object layout is not further broken out here.
// ============================================================================

}  // namespace wh::xgenaimodule::BehaviorTree
