#pragma once

#include <cstdint>

#include "I_Node.h"          // I_Node, I_DebugNode, E_NodeStatus
#include "C_Node.h"          // C_Node (leaf base, object 0x28)
#include "C_NodeWrapper.h"   // C_NodeWrapper<TNode, TBase, TContext>
#include "C_NodeFactory.h"   // C_NodeFactoryImpl<>, C_DefaultNodeContextCasting<>, C_NodeContextPool<>
#include "NodeAttribute.h"   // NodeAttribute<>, EnumNodeAttribute<>

// ===========================================================================
//  C_VarOperation  --  Warhorse Behavior-Tree leaf node (system: flow)
//
//  A BT <VarOperation> element (registered under the "Variables" node group)
//  performs an operation on a brain/blackboard ARRAY variable. The node object
//  is stateless (size 0x28, the C_Node leaf layout); per-(entity,node) runtime
//  state lives in a pooled S_VarOperationContext that the runtime passes to the
//  node virtuals -- the shared WH C_NodeWrapper / C_NodeContextPool design.
//
//  XML -> C++ -> engine chain (VERIFIED):
//    <VarOperation .../>  (element name "VarOperation", group "Variables")
//        -> registered by C_NodeFactory_VarOperation
//             (registrar sub_1813DC068:
//                 wh::framework::StringHash("VarOperation"),
//                 wh::framework::StringHash("Variables"))
//        -> instantiated by C_NodeFactoryImpl<C_VarOperation,
//                 C_DefaultNodeContextCasting<S_VarOperationContext>>
//             create funcs sub_1813D6E9C / sub_1813D6FD4 / sub_1813DAF8C:
//                 allocate 0x28 bytes, run ctor sub_1813C56C0, then bind XML
//                 (vptr+0x120 = SetCreator, vptr+0x70 = LoadFromXml)
//        -> per-entity context pooled by
//                 C_NodeContextPool<S_VarOperationContext,
//                                   C_DefaultNodeContextCasting<S_VarOperationContext>>
//
//  ---------------------------------------------------------------------------
//  RTTI / object identity  (VERIFIED -- get_string / find_regex / name lookups)
//  ---------------------------------------------------------------------------
//   Node RTTI name        @ 0x182ab7c30  ".?AVC_VarOperation@BehaviorTree@xgenaimodule@wh@@"
//   Node TypeDescriptor   @ 0x182ab7c20  (= name - 0x10), RVA 0x2ab7c20
//   Node vtable _0        @ 0x1821c2e60  ??_7C_VarOperation...6B@_0   (object +0x00, primary/I_Node)
//   Node vtable _1        @ 0x1821c2e98  ??_7C_VarOperation...6B@     (object +0x08, secondary/I_DebugNode)
//   Node COL _0           @ 0x182444170  ??_R4C_VarOperation...6B@_0  (at 0x1821c2e58)
//   Node COL _1           @ 0x182444198  ??_R4C_VarOperation...6B@    (at 0x1821c2e90)
//
//   Wrapper RTTI name     @ 0x182ab7c80  ".?AV?$C_NodeWrapper@VC_VarOperation@...VC_Node@...US_VarOperationContext@..."
//   Wrapper vtable        @ 0x1821c2bf0  ??_7?$C_NodeWrapper@VC_VarOperation...@@6B@  (full 60-slot I_Node vtable)
//
//   Context RTTI name     @ 0x182ab8c00  ".?AUS_VarOperationContext@BehaviorTree@xgenaimodule@wh@@"   (U = struct)
//   Context-pool RTTI     @ 0x182ab79e0  ".?AV?$C_NodeContextPool@US_VarOperationContext@...@@"
//   Enum-attr RTTI        @ 0x182ab8c50  ".?AV?$EnumNodeAttribute@W4E_VarOperations@S_VarOperationContext@...@@"
//                                         => the 'operation' attribute is an
//                                            EnumNodeAttribute<S_VarOperationContext::E_VarOperations>
//                                            (W4 mangling = a 32-bit enum)
//
//   Factory RTTI name     @ 0x182ab7b10  ".?AVC_NodeFactory_VarOperation@BehaviorTree@xgenaimodule@wh@@"
//   Factory-impl RTTI     @ 0x182ab7b60  ".?AV?$C_NodeFactoryImpl@VC_VarOperation@...V?$C_DefaultNodeContextCasting@US_VarOperationContext@...@@"
//   Factory object vtable @ 0x1823471a8  (COL ??_R4C_NodeFactory_VarOperation @ 0x1825390e8)
//   Factory-impl vtable   @ 0x1823471f0  ??_7?$C_NodeFactoryImpl@VC_VarOperation...@@6B@
//
//  ---------------------------------------------------------------------------
//  Construction  (VERIFIED -- decompiled)
//  ---------------------------------------------------------------------------
//   wh::xgenaimodule::BehaviorTree::C_VarOperation::base_ctor_180586330  (sub_180586330)
//        *(this+0x00) = *(this+0x08) = &C_Node::vftable
//        *(this+0x10) = 0
//        *(this+0x18) = *(creatorDesc+0x18)            (m_nodeId copy)
//        *(this+0x00) = *(this+0x08) =
//            &C_NodeWrapper<C_VarOperation, C_Node, S_VarOperationContext>::vftable  (@0x1821c2bf0)
//        *(this+0x20) = 0
//     ==> the demangled vftable symbol DIRECTLY VERIFIES both the base chain
//         C_NodeWrapper<C_VarOperation, C_Node, S_VarOperationContext> and the
//         context type name S_VarOperationContext.
//
//   wh::xgenaimodule::BehaviorTree::C_VarOperation::ctor_1805863C8  (sub_1805863C8)
//        1. calls base_ctor_180586330(this, creatorDesc)
//        2. *(this+0x00) = *(this+0x08) = &C_VarOperation::vftable  (_1 @0x1821c2e98 / _0 @0x1821c2e60)
//        3. attribute-default copy loop over the runtime offset vector
//           xmmword_1836F4C30: sub_18028DF58((char*)this+off, (char*)creatorDesc+off)
//           (the offset vector is built at module init and is empty in the
//            static image, so the per-attribute field offsets are not statically readable)
//
//   wh::xgenaimodule::BehaviorTree::C_VarOperation::clone_1813C56C0  (sub_1813C56C0)
//        copy/clone path used by the factory create funcs; also stores both
//        C_VarOperation vtables (_0 @0x1813c56de, _1 @0x1813c56d2).
//  ===========================================================================

namespace wh::xgenaimodule::BehaviorTree {

// Forward decl: the context owns the operation enum (see RTTI
// EnumNodeAttribute<E_VarOperations@S_VarOperationContext>).
struct S_VarOperationContext;

// ---------------------------------------------------------------------------
// S_VarOperationContext -- per-(entity,node) runtime context.
//
// VERIFIED to exist and to be a STRUCT named S_VarOperationContext:
//   - RTTI ".?AUS_VarOperationContext@BehaviorTree@xgenaimodule@wh@@" (@0x182ab8c00)
//   - it is the TContext template argument of the node's C_NodeWrapper base
//     (read from the demangled wrapper vftable symbol in base_ctor_180586330)
//   - it is pooled via C_NodeContextPool<S_VarOperationContext, ...> (@0x182ab79e0)
//   - it OWNS the nested enum E_VarOperations (the 'operation' attribute is an
//     EnumNodeAttribute<S_VarOperationContext::E_VarOperations>, RTTI @0x182ab8c50)
//
// The runtime hands this context to the node virtuals as the `void* context`
// argument; the pool sizes/keys it per instance.
// ---------------------------------------------------------------------------
struct S_VarOperationContext /* : S_BaseNodeContext [UNVERIFIED base] */ {
    // -----------------------------------------------------------------------
    // E_VarOperations -- value of the 'operation' XML attribute.
    // VERIFIED (RTTI): the enum is nested in S_VarOperationContext and is bound
    // through EnumNodeAttribute<E_VarOperations>; the W4 mangling proves it is a
    // 32-bit (int) enum.
    //
    // [UNVERIFIED] The enum CONSTANTS and their integer VALUES: the
    // EnumNodeAttribute name->value string table was not located this session
    // (full .rdata string scans time out at the IDA bridge's 15s limit; only
    // targeted find_regex worked). Find / PushBack / FastPop / Reinit are the
    // operation names from the BT XML schema / task brief, NOT confirmed from a
    // value table or a dispatch switch. Re-derive from the EnumNodeAttribute
    // descriptor before relying on the ordering/values.
    // -----------------------------------------------------------------------
    enum class E_VarOperations : int32_t {
        Find,        // [UNVERIFIED value/order]
        PushBack,    // [UNVERIFIED value/order]
        FastPop,     // [UNVERIFIED value/order]
        Reinit,      // [UNVERIFIED value/order]
    };

    // [UNVERIFIED] Concrete member layout, size, and base struct. A decompile
    // of the per-tick operation logic and a clean read of the context body were
    // blocked by repeated IDA-bridge timeouts. Members below are the EXPECTED
    // shape only and carry no hard offsets. If a shared per-node context header
    // exists (see S_BaseNodeContext in C_Composite.h / C_NodeContext.h) inherit
    // it instead of restating its fields.
    //
    // E_VarOperations m_operation;     // parsed 'operation'
    // /* resolved 'varName' variable handle, parsed 'argument', op scratch */
};

// ---------------------------------------------------------------------------
// C_VarOperation -- the BT node policy/type.
//
// Base chain VERIFIED from the C_NodeWrapper<...>::vftable symbol written by
// base_ctor_180586330 (and corroborated by the wrapper/context/factory RTTI):
//
//     C_VarOperation
//        : C_NodeWrapper<C_VarOperation /*TNode policy*/,
//                        C_Node          /*TBase = leaf*/,
//                        S_VarOperationContext /*TContext*/>
//
// VERIFIED object size 0x28 (the factory create funcs allocate 0x28 bytes for
// the node before invoking the ctor). As with every concrete WH BT node the
// stateless TNode policy methods are inlined into the wrapper vtable rather
// than emitted as out-of-line members, so C_VarOperation declares no data
// members of its own; per-tick state lives in S_VarOperationContext. The
// policy callbacks are declared below for documentation only.
// ---------------------------------------------------------------------------
class C_VarOperation
    : public C_NodeWrapper<C_VarOperation, C_Node, S_VarOperationContext>
{
    // No own data members - object == sizeof(C_Node) == 0x28 (VERIFIED: base
    // ctor sub_180586330 writes ONLY the C_Node fields - m_pNodeData=0 @+0x10,
    // m_nodeId @+0x18, m_pCreator=0 @+0x20 - nothing past +0x20; the factory
    // create funcs sub_1813D6E9C / sub_1813D6FD4 / sub_1813DAF8C allocate 0x28).
    //
    // ---- Parsed XML attributes (NOT stored on the node) --------------------
    // The attributes are owned by the node CREATOR (the C_NodeFactory_VarOperation
    // product) and bound via LoadFromXml; storing them as node members here would
    // inflate the node past its verified 0x28 size (same correction as
    // C_RemoveItem / C_AddBuff).  VERIFIED attribute kinds, documentation only:
    //   "operation" : EnumNodeAttribute<S_VarOperationContext::E_VarOperations>
    //                 (RTTI ".?AV?$EnumNodeAttribute@W4E_VarOperations@...@@";
    //                  W4 mangling => 32-bit enum) - VERIFIED kind.
    //   "varName" / "argument" : [UNVERIFIED] NodeAttribute<> element types and
    //                 bind offsets - the ctor's per-field offset vector
    //                 xmmword_1836F4C30 is runtime-populated (empty in the static
    //                 image), so the attribute set cannot be enumerated statically.
    //
    // ---- Inlined policy callbacks (routed through C_NodeWrapper) ------------
    // [UNVERIFIED] signatures/bodies, so NOT declared here (declaring them would
    // assert a signature we have not proven). The wrapper vtable (@0x1821c2bf0)
    // carries the node-specific overrides at the standard I_Node slots, but the
    // concrete per-operation Update body/signature were not isolated.
};
static_assert(sizeof(C_VarOperation) == 0x28);   // VERIFIED: ctor sub_180586330 / create funcs alloc 0x28

}  // namespace wh::xgenaimodule::BehaviorTree
