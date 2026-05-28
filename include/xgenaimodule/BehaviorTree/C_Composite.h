#pragma once

#include <cstdint>
#include <vector>
#include "C_Node.h"
#include "C_NodeWrapper.h"

namespace wh::xgenaimodule::BehaviorTree {

struct S_BaseNodeContext {};
struct S_SwitchBaseContext {};

// ---------------------------------------------------------------------------
// C_Composite — native multi-child base (directly inherits C_Node).
//
// RTTI: .?AVC_Composite@BehaviorTree@xgenaimodule@wh@@
// Size: 0x40 bytes
// VERIFIED from dtor sub_180585954: frees vector at a1[5]/[6]/[7] (+0x28/+0x30/+0x38)
// ---------------------------------------------------------------------------
class C_Composite : public C_Node {
public:
    const char* GetNodeCategory() const override { return "Composite"; } // [6]

    void TerminateChildren() override;          // [53]
    void unk_55() override;                     // [55]
    void unk_56() override;                     // [56]
    void OnSuspend() override;                  // [57]
    void OnResume() override;                   // [58]
    void OnAbort() override;                    // [59]

    std::vector<I_Node*> m_children;            // +0x28  child node array (0x18)
};
static_assert(sizeof(C_Composite) == 0x40);

// ---------------------------------------------------------------------------
// C_SwitchBase — CRTP wrapper over C_Composite with switch-case child map.
//
// RTTI: .?AVC_SwitchBase@BehaviorTree@xgenaimodule@wh@@
// Size: 0x58 bytes
// VERIFIED from dtor sub_180586C70:
//   inherits C_NodeWrapper<C_SwitchBase, C_Composite, S_SwitchBaseContext>
//   frees second vector at a1[8]/[9]/[0xA] (+0x40/+0x48/+0x50)
//   then chains to C_Composite dtor for m_children cleanup
// ---------------------------------------------------------------------------
class C_SwitchBase
    : public C_NodeWrapper<C_SwitchBase, C_Composite, S_SwitchBaseContext>
{
public:
    std::vector<void*> m_switchCases;           // +0x40  case/branch data (0x18)
};
static_assert(sizeof(C_SwitchBase) == 0x58);

// ---------------------------------------------------------------------------
// C_FixedComposite<N> — CRTP wrapper over C_Node with fixed child slots.
//
// RTTI: .?AV?$C_FixedComposite@$0<N>@@BehaviorTree@xgenaimodule@wh@@
// VERIFIED: C_FixedComposite<2> inherits
//   C_NodeWrapper<C_FixedComposite<2>, C_Node, S_BaseNodeContext> → C_Node
// Size: 0x28 + N*8 + additional state (UNVERIFIED exact layout per N)
// ---------------------------------------------------------------------------
template<int N>
class C_FixedComposite
    : public C_NodeWrapper<C_FixedComposite<N>, C_Node, S_BaseNodeContext>
{
public:
    int32_t GetChildCount() const override { return N; }    // [9]

    I_Node* m_fixedChildren[N];                 // +0x28  inline child pointers
};

}  // namespace wh::xgenaimodule::BehaviorTree
