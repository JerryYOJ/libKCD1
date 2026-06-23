#pragma once

#include <cstdint>
#include "C_CombatAutomationAction.h"

namespace wh::combatmodule {

// ---------------------------------------------------------------------------
// C_CombatAutomationWeapons -- AI weapon-selection/switching behaviour; embedded
// at C_CombatAutomation+0x620.
//
// RTTI: .?AVC_CombatAutomationWeapons@combatmodule@wh@@  (descriptor rva 0x2A01B50)
// vtable @ 0x1821C6AE0 ; ctor sub_180590DC0
// Inherits: C_CombatAutomationAction. Size: 0xC8.
// ---------------------------------------------------------------------------
class C_CombatAutomationWeapons : public C_CombatAutomationAction {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_CombatAutomationWeapons;
    ~C_CombatAutomationWeapons() override = default;
    void Reset() override {}
    E_CombatSubsystem GetSubsystemId() const override { return COMBAT_SUB_AUTOMATION_ACTION; }
    const char* GetName() const override { return "AutomationWeapons"; }

    uint8_t _state[0xC8 - 0x30];   // +0x30  weapon-selection state; not field-level RE'd
};
static_assert(sizeof(C_CombatAutomationWeapons) == 0xC8);

}  // namespace wh::combatmodule
