#pragma once

#include <cstdint>
#include "C_CombatAutomationAction.h"

namespace wh::combatmodule {

// ---------------------------------------------------------------------------
// C_CombatAutomationRiposte -- AI riposte/master-strike decision behaviour;
// embedded at C_CombatAutomation+0x288.
//
// RTTI: .?AVC_CombatAutomationRiposte@combatmodule@wh@@  (descriptor rva 0x2A01AC0)
// vtable @ 0x182215748 ; ctor sub_1806E8E28
// Inherits: C_CombatAutomationAction. Size: 0x48.
// ---------------------------------------------------------------------------
class C_CombatAutomationRiposte : public C_CombatAutomationAction {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_CombatAutomationRiposte;
    ~C_CombatAutomationRiposte() override = default;
    void Reset() override {}
    E_CombatSubsystem GetSubsystemId() const override { return COMBAT_SUB_AUTOMATION_ACTION; }
    const char* GetName() const override { return "AutomationRiposte"; }

    uint8_t _state[0x48 - 0x30];   // +0x30  riposte-timing state; not field-level RE'd
};
static_assert(sizeof(C_CombatAutomationRiposte) == 0x48);

}  // namespace wh::combatmodule
