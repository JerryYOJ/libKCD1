#pragma once

#include <cstdint>
#include "C_CombatAutomationAction.h"

namespace wh::combatmodule {

// ---------------------------------------------------------------------------
// C_CombatAutomationShout -- AI combat-shout (voice) behaviour; embedded at
// C_CombatAutomation+0x5B8.
//
// RTTI: .?AVC_CombatAutomationShout@combatmodule@wh@@  (descriptor rva 0x2A01BD8)
// vtable @ 0x1821B7348 ; ctor sub_1804F479C
// Inherits: C_CombatAutomationAction. Size: 0x68.
// ---------------------------------------------------------------------------
class C_CombatAutomationShout : public C_CombatAutomationAction {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_CombatAutomationShout;
    ~C_CombatAutomationShout() override = default;
    void Reset() override {}
    E_CombatSubsystem GetSubsystemId() const override { return COMBAT_SUB_AUTOMATION_ACTION; }
    const char* GetName() const override { return "AutomationShout"; }

    uint8_t _state[0x68 - 0x30];   // +0x30  shout-timing state; not field-level RE'd
};
static_assert(sizeof(C_CombatAutomationShout) == 0x68);

}  // namespace wh::combatmodule
