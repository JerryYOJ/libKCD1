#pragma once

#include <cstdint>
#include "C_CombatAutomationAction.h"

namespace wh::combatmodule {

// ---------------------------------------------------------------------------
// C_CombatAutomationGuard -- AI guard-stance behaviour; embedded at
// C_CombatAutomation+0x558.
//
// RTTI: .?AVC_CombatAutomationGuard@combatmodule@wh@@  (descriptor rva 0x2A01A40)
// vtable @ 0x1821B73C0 ; ctor sub_1804F47F8
// Inherits: C_CombatAutomationAction. Size: 0x60.
// NOTE: GetName() returns "AutomationGaurd" -- a misspelling baked into the binary.
// ---------------------------------------------------------------------------
class C_CombatAutomationGuard : public C_CombatAutomationAction {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_CombatAutomationGuard;
    ~C_CombatAutomationGuard() override = default;
    void Reset() override {}
    E_CombatSubsystem GetSubsystemId() const override { return COMBAT_SUB_AUTOMATION_ACTION; }
    const char* GetName() const override { return "AutomationGaurd"; }   // sic (binary typo)

    uint8_t _state[0x60 - 0x30];   // +0x30  guard-decision state; not field-level RE'd
};
static_assert(sizeof(C_CombatAutomationGuard) == 0x60);

}  // namespace wh::combatmodule
