#pragma once
#include <cstdint>

namespace wh {

// -----------------------------------------------
// I_ReadinessDebuggable — root of the Warhorse readiness interface chain
// -----------------------------------------------
// RTTI: .?AVI_ReadinessDebuggable@wh@@
//
// 2 virtual slots, NO virtual destructor (verified): the secondary vtable of
// C_FastTravel (??_7C_FastTravel@playermodule@wh@@6B@_0 @ 0x1826dd728) holds
// exactly two entries before the next COL (0x1824EE8E8), both
// _guard_check_icall_nop — i.e. the debug hooks are compiled out in retail.
// The same two stubbed slots lead the vtables of every deriver
// (C_PlayerProfileWHManager 0x1826a2318, C_SaveGameManager 0x1826a31e8); the
// destructor is introduced later by the concrete class, never here.
//
// (The previous "7 slots / virtual dtor" note was a miscount — it ran past the
//  COL into an adjacent vtable. See feedback_vtable_validation.)

class I_ReadinessDebuggable {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_I_ReadinessDebuggable;
    virtual void DebugReadiness0() = 0;   // [0] 0x00  debug hook (name unverified, stubbed in retail)
    virtual void DebugReadiness1() = 0;   // [1] 0x08  debug hook (name unverified, stubbed in retail)
};

}  // namespace wh
