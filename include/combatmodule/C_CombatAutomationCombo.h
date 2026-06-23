#pragma once

#include <cstdint>
#include "C_CombatAutomationAction.h"

namespace wh::combatmodule {

// ---------------------------------------------------------------------------
// C_CombatAutomationCombo -- AI combo-continuation decision behaviour; embedded
// at C_CombatAutomation+0x2D0.
//
// RTTI: .?AVC_CombatAutomationCombo@combatmodule@wh@@  (descriptor rva 0x2A01A00)
// vtable @ 0x18220EDE0 ; ctor sub_1806E1F5C
// Inherits: C_CombatAutomationAction. Size: 0x60.
// ---------------------------------------------------------------------------
class C_CombatAutomationCombo : public C_CombatAutomationAction {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_CombatAutomationCombo;
    ~C_CombatAutomationCombo() override = default;
    void Reset() override {}
    E_CombatSubsystem GetSubsystemId() const override { return COMBAT_SUB_AUTOMATION_ACTION; }
    const char* GetName() const override { return "AutomationCombo"; }

    uint8_t _state[0x60 - 0x30];   // +0x30  combo-decision state; not field-level RE'd
};
static_assert(sizeof(C_CombatAutomationCombo) == 0x60);

}  // namespace wh::combatmodule
