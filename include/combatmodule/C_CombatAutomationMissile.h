#pragma once

#include <cstdint>
#include "C_CombatAutomationAction.h"

namespace wh::combatmodule {

// ---------------------------------------------------------------------------
// C_CombatAutomationMissile -- AI ranged/missile (bow, thrown) behaviour; embedded
// at C_CombatAutomation+0x6E8 (last sub-object, runs to the 0x758 end).
//
// RTTI: .?AVC_CombatAutomationMissile@combatmodule@wh@@  (descriptor rva 0x2A01980)
// vtable @ 0x1821B72D0 ; ctor sub_1804F46EC
// Inherits: C_CombatAutomationAction. Size: 0x70.
// ---------------------------------------------------------------------------
class C_CombatAutomationMissile : public C_CombatAutomationAction {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_CombatAutomationMissile;
    ~C_CombatAutomationMissile() override = default;
    void Reset() override {}
    E_CombatSubsystem GetSubsystemId() const override { return COMBAT_SUB_AUTOMATION_ACTION; }
    const char* GetName() const override { return "AutomationMissile"; }

    uint8_t _state[0x70 - 0x30];   // +0x30  missile-timing state; not field-level RE'd
};
static_assert(sizeof(C_CombatAutomationMissile) == 0x70);

}  // namespace wh::combatmodule
