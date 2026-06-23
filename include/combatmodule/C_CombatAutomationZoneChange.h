#pragma once

#include <cstdint>
#include "C_CombatAutomationAction.h"

namespace wh::combatmodule {

// ---------------------------------------------------------------------------
// C_CombatAutomationZoneChange -- AI attack-zone (direction) switching behaviour;
// embedded at C_CombatAutomation+0x330. The largest automation sub-object.
//
// RTTI: .?AVC_CombatAutomationZoneChange@combatmodule@wh@@  (descriptor rva 0x2A01B90)
// vtable @ 0x1821B7438 ; ctor sub_1804F4854 (reserves a 0x14-stride vector, inits
//   weight floats 3/7/1/3, a -1 target, masks a flag &=0xFC)
// Inherits: C_CombatAutomationAction. Size: 0x228.
// ---------------------------------------------------------------------------
class C_CombatAutomationZoneChange : public C_CombatAutomationAction {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_CombatAutomationZoneChange;
    ~C_CombatAutomationZoneChange() override = default;
    void Reset() override {}
    E_CombatSubsystem GetSubsystemId() const override { return COMBAT_SUB_AUTOMATION_ACTION; }
    const char* GetName() const override { return "AutomationZoneChange"; }

    // +0x30..0x228: zone-change state -- a 0x14-stride candidate vector, per-zone
    // weight floats, a -1 target-zone sentinel, timers. Not field-level RE'd.
    uint8_t _state[0x228 - 0x30];   // +0x30
};
static_assert(sizeof(C_CombatAutomationZoneChange) == 0x228);

}  // namespace wh::combatmodule
