#pragma once

#include <cstdint>

// ===========================================================================
// wh::rpgmodule::E_CrimeIconLevel  -  a location's "wanted" / crime-icon level.
// ===========================================================================
// Value domain of I_Location::GetWantedLevel / GetOwnWantedLevel / SetWantedLevel
// and of C_RPGLocation::m_selfWantedLevel.
//
// SOURCE: AI TypeDefinitions.xml:5648  <Enum name="crimeIconLevel"> { none, fine, jail }
//   (members implicitly 0-indexed in declaration order). The enum is carried by the
//   BT message  location:crimeIconLevelUpdate { sender:wuid, level:crimeIconLevel }
//   (sb_combat.xml subbrain "determineCrimeIconLevel", TypeDefinitions.xml:5658).
// Stored/compared as a 32-bit int in the binary: SetWantedLevel writes a DWORD,
// GetWantedLevel returns/compares as int.
// [CONFIRMED values & XML names; the C++ identifier E_CrimeIconLevel is INFERRED]
// ===========================================================================

namespace wh::rpgmodule {

enum class E_CrimeIconLevel : int32_t {
    None = 0,   // "none"  no wanted state
    Fine = 1,   // "fine"  pay-a-fine tier
    Jail = 2,   // "jail"  arrest / jail tier
};

}  // namespace wh::rpgmodule
