#pragma once

#include <cstdint>

namespace wh::combatmodule {

// ---------------------------------------------------------------------------
// I_CombatAutomation -- pure interface; the multiple-inheritance secondary base of
// C_CombatAutomation (its sub-object sits at C_CombatAutomation+0x18). Data-less, so
// it contributes only its own vtable pointer to the layout.
//
// RTTI: .?AVI_CombatAutomation@combatmodule@wh@@  (descriptor rva 0x2A025B0)
// Secondary vtable @ 0x1821B70F0.
//
// NOTE: the real interface vtable has a large slot count that has not yet been
// enumerated; this declaration models the base for correct MI layout (so
// C_CombatAutomation needs no raw vtable pointer). Add the concrete virtual slots
// here when they are RE'd.
// ---------------------------------------------------------------------------
class I_CombatAutomation {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_I_CombatAutomation;
    virtual ~I_CombatAutomation() = default;
};

}  // namespace wh::combatmodule
