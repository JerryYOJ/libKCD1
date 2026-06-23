#pragma once

#include <cstdint>

namespace wh::combatmodule {

// ---------------------------------------------------------------------------
// E_CombatZoneId -- directional combat zones.
//
// VERIFIED: from combat_zone.xml in Tables.pak.
// Each zone corresponds to a guard/attack direction in the star combat system.
// Zone 2 (upper_right) is the default zone (default_zone="True").
// ---------------------------------------------------------------------------
enum class E_CombatZoneId : int32_t {
    Undefined  = -1,
    Head       = 0,   // "head"        — top stab
    UpperLeft  = 1,   // "upper_left"  — angles 135°-205°
    UpperRight = 2,   // "upper_right" — angles 325°-45° (DEFAULT)
    LowerLeft  = 3,   // "lower_left"  — angles 205°-270°
    LowerRight = 4,   // "lower_right" — angles 270°-325°
    Center     = 5,   // "center"      — radius 0 (thrust/stab)
};

}  // namespace wh::combatmodule
