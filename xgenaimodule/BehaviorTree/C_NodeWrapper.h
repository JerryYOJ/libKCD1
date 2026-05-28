#pragma once

#include <cstdint>

namespace wh::xgenaimodule::BehaviorTree {

// ---------------------------------------------------------------------------
// C_NodeWrapper<TNode, TBase, TContext> — template wrapping a behavior policy.
//
// RTTI pattern:
//   .?AV?$C_NodeWrapper@V<TNode>@...@V<TBase>@...@U<TContext>@...@@...@@
//
// Template parameters:
//   TNode    — stateless behavior policy class. Provides methods:
//              OnInitialize(TContext&), Update(TContext&) → Status,
//              OnTerminate(TContext&), HandleEvent(TContext&, Event&),
//              LoadFromXml(XmlNode, LoadContext).
//              Has NO data members — does NOT appear in the RTTI base list.
//              Pure compile-time dispatch: its methods are inlined into the
//              wrapper's vtable entries.
//
//   TBase    — structural base class determining child management strategy.
//              C_Node (leaf, 0x28), C_Decorator (1 child, 0x30),
//              C_Composite (N children, 0x40), C_FixedComposite<N>, C_Gate, etc.
//              The wrapper inherits TBase — this IS the inheritance chain.
//
//   TContext — per-entity runtime data struct. NOT stored in the node object.
//              Heap-allocated per entity by NodeCreator<C_NodeWrapper>::
//              AllocateRuntimeData(). Passed through UpdateContext::runtimeData
//              as void*, cast to TContext& by the wrapper's vtable methods.
//              Freed when the node completes for that entity.
//
// Size: sizeof(TBase) — no additional data members.
// VERIFIED: all C_Node-based wrappers share the same dtor (frees 0x28),
//           regardless of TNode or TContext type.
// ---------------------------------------------------------------------------
template<typename TNode, typename TBase, typename TContext>
class C_NodeWrapper : public TBase {
public:
    using NodeLogic   = TNode;
    using RuntimeData = TContext;

    // The wrapper generates vtable overrides that delegate to TNode:
    //
    // void OnInitialize(void* ctx) override {
    //     NodeLogic::OnInitialize(*static_cast<RuntimeData*>(ctx));
    // }
    // E_NodeStatus Update(void* ctx) override {
    //     return NodeLogic::Update(*static_cast<RuntimeData*>(ctx));
    // }
    // void OnTerminate(void* ctx) override {
    //     NodeLogic::OnTerminate(*static_cast<RuntimeData*>(ctx));
    // }
    // void HandleEvent(void* ctx, void* event) override {
    //     NodeLogic::HandleEvent(*static_cast<RuntimeData*>(ctx), event);
    // }
    // void LoadFromXml(void* xml, void* loadCtx) override {
    //     NodeLogic::LoadFromXml(xml, loadCtx);
    // }
    //
    // No additional data members — sizeof(C_NodeWrapper) == sizeof(TBase).
};

}  // namespace wh::xgenaimodule::BehaviorTree
