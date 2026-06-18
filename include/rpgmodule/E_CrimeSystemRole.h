#pragma once

#include <cstdint>

namespace wh::rpgmodule {

// -----------------------------------------------
// E_CrimeSystemRole -- which side of the law a soul is on.
// -----------------------------------------------
// Stored as the soul_crime_role_id column of the rpg/social_class table
// (S_SocialClass::m_crimeRoleId, +0x14). Seeded into the brain variable
// b_soul.crimeSystemRole at brain init (Lua GetCrimeSystemRole = social-class default),
// after which a crimeSystemRoleOverride brain message can change it at runtime.
// This is the value the crime AI tests to decide "is this NPC a guard?" -- Soldier
// (town/world guard) and Circator (monastery enforcer) are the crime authorities.
//
// Values are DATA-defined (modding.sql soul_crime_role table + ai/TypeDefinitions.xml
// <Enum name="crimeSystemRole">, two independent sources agree); they are NOT present
// as symbols/strings in WHGame.dll -- the binary only ever moves the raw int.
enum class E_CrimeSystemRole : int32_t {
    None     = 0,   // player, wild/tamed animals, dog companion
    Civilian = 1,   // villagers, nobles, priests, merchants, beggars, craftsmen...
    Soldier  = 2,   // GUARD: social classes soldier / officer / bailiff / watchman
    Renegade = 3,   // bandits, cumans, poachers, mercenaries -- and security / fake_soldier
    Monk     = 4,
    Circator = 5,   // monastery enforcer (the "guard" inside a monastery)
};

}  // namespace wh::rpgmodule
