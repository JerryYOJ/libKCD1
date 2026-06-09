#pragma once

#include <cstdint>

namespace wh::xgenaimodule::BehaviorTree {

// ---------------------------------------------------------------------------
// I_DebugNode — secondary vtable interface for BT node debugging.
//
// RTTI: .?AVI_DebugNode@BehaviorTree@xgenaimodule@wh@@
// Embedded as secondary vtable at +0x08 in all BT node objects.
// 6 virtual methods.
// ---------------------------------------------------------------------------
class I_DebugNode {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_I_DebugNode;
    virtual ~I_DebugNode() = default;           // [0]
    virtual void unk_debug_1() {}               // [1] nop
    virtual void GetDebugText(void* out) {}     // [2]
    virtual void unk_debug_3() {}               // [3] nop
    virtual bool unk_debug_4() { return false; } // [4]
    virtual void unk_debug_5() {}               // [5] nop
};

}  // namespace wh::xgenaimodule::BehaviorTree
