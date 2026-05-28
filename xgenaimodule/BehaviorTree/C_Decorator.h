#pragma once

#include <cstdint>
#include "C_Node.h"

namespace wh::xgenaimodule::BehaviorTree {

// ---------------------------------------------------------------------------
// C_Decorator — native single-child base (directly inherits C_Node).
//
// RTTI: .?AVC_Decorator@BehaviorTree@xgenaimodule@wh@@
// Size: 0x30 bytes (0x28 from C_Node + 0x08 child pointer)
// VERIFIED: AtomicDecorator wrapper dtor frees 0x30.
// ---------------------------------------------------------------------------
class C_Decorator : public C_Node {
public:
    const char* GetNodeCategory() const override { return "Decorator"; } // [6]
    int32_t GetChildCount() const override { return 1; }                 // [9]

    void OnChildInitialized() override;         // [47]
    void OnUpdate(void*) override;              // [49]
    void TerminateChildren() override;          // [53]
    void unk_55() override;                     // [55]
    void unk_56() override;                     // [56]
    void OnSuspend() override;                  // [57]
    void OnResume() override;                   // [58]
    void OnAbort() override;                    // [59]

    I_Node*     m_pChild;       // +0x28  single child node
};
static_assert(sizeof(C_Decorator) == 0x30);

// ---------------------------------------------------------------------------
// C_WrapperDecorator — decorator variant.
// RTTI: .?AVC_WrapperDecorator@BehaviorTree@xgenaimodule@wh@@
// ---------------------------------------------------------------------------
class C_WrapperDecorator : public C_Decorator {
};
static_assert(sizeof(C_WrapperDecorator) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
