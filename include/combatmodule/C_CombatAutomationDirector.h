#pragma once

#include <cstdint>
#include "C_CombatAutomationAction.h"

namespace wh::combatmodule {

// ---------------------------------------------------------------------------
// C_CombatAutomationDirector -- top-level automation arbiter; embedded at
// C_CombatAutomation+0xC0. Coordinates the other automation behaviours.
//
// RTTI: .?AVC_CombatAutomationDirector@combatmodule@wh@@  (descriptor rva 0x2A01260)
// vtable @ 0x1821B7038
// Built inline in the aggregate ctor sub_1804F44B0 (base sub_1805FA600 then vtable swap).
// Inherits: C_CombatAutomationAction. Size: 0x80.
// ---------------------------------------------------------------------------
class C_CombatAutomationDirector : public C_CombatAutomationAction {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_CombatAutomationDirector;
    ~C_CombatAutomationDirector() override = default;
    void Reset() override {}                                                                 // [1] no-op stub in binary
    E_CombatSubsystem GetSubsystemId() const override { return COMBAT_SUB_AUTOMATION_ACTION; } // [2] sub_1806FAAB0 -> 0x19
    const char* GetName() const override { return "AutomationDirector"; }                    // [3] sub_1806FBB10

    // +0x30..0x80: director state -- several int64 "last/next time" sentinels (init -100000)
    // + flags/counters. Not field-level RE'd (writers not traced).
    uint8_t _state[0x80 - 0x30];   // +0x30
};
static_assert(sizeof(C_CombatAutomationDirector) == 0x80);

}  // namespace wh::combatmodule
