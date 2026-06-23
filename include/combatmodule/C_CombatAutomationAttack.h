#pragma once

#include <cstdint>
#include "C_CombatAutomationAction.h"

namespace wh::combatmodule {

// ---------------------------------------------------------------------------
// C_CombatAutomationAttack -- AI auto-attack timing/decision behaviour; embedded
// at C_CombatAutomation+0x1C8.
//
// RTTI: .?AVC_CombatAutomationAttack@combatmodule@wh@@  (descriptor rva 0x2A01A80)
// vtable @ 0x182204740 ; ctor sub_1806D6108
// Inherits: C_CombatAutomationAction. Size: 0xC0.
// ---------------------------------------------------------------------------
class C_CombatAutomationAttack : public C_CombatAutomationAction {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_CombatAutomationAttack;
    ~C_CombatAutomationAttack() override = default;
    void Reset() override {}
    E_CombatSubsystem GetSubsystemId() const override { return COMBAT_SUB_AUTOMATION_ACTION; }
    const char* GetName() const override { return "AutomationAttack"; }

    // +0x30..0xC0: attack-timing state -- sentinel timers (init -100000), an LCG RNG
    // state + derived [0,1) roll, and counter snapshots. Not field-level RE'd.
    uint8_t _state[0xC0 - 0x30];   // +0x30
};
static_assert(sizeof(C_CombatAutomationAttack) == 0xC0);

}  // namespace wh::combatmodule
