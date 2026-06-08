#pragma once

#include <cstdint>

// ===========================================================================
// wh::rpgmodule::E_RPGSkill  -  the 33 character skills (skill_id).
// ===========================================================================
// Index into S_PerkSubsystem::m_skillLevels (soul+0x540) and S_PerkPointCounters::skillPoints.
// Also the value of S_PerkDefinition::skillSelector (with Count(0x21) meaning "none / main level").
//
// SOURCE: VERIFIED verbatim from the game table Libs/Tables/rpg/skill.xml (columns skill_id +
// skill_name). Enumerators are PascalCase of skill_name. "hidden=True" rows are crafting/unused
// skills kept for id continuity; "induced=N" notes the parent skill that levels this one.
// ===========================================================================

namespace wh::rpgmodule {

enum class E_RPGSkill : int32_t {
    Stealth         = 0,
    HorseRiding     = 1,
    Fencing         = 2,
    Bard            = 3,   // hidden
    Lockpicking     = 4,
    Pickpocketing   = 5,
    Alchemy         = 6,
    Cooking         = 7,   // hidden
    Repairing       = 8,   // UI: "Maintenance"/"Sharpening"
    Smithing        = 9,   // hidden
    Fishing         = 10,  // hidden
    Mining          = 11,  // hidden
    FirstAid        = 12,  // hidden
    Drinking        = 13,
    Hunter          = 14,
    Defense         = 15,
    WeaponSword     = 16,  // induced from Fencing(2)
    WeaponAxe       = 17,  // induced from Fencing(2)
    WeaponBow       = 18,
    WeaponCrossbow  = 19,  // hidden
    WeaponShield    = 20,  // hidden
    WeaponMace      = 21,  // induced from Fencing(2)
    WeaponDagger    = 22,  // hidden
    WeaponLarge     = 23,  // hidden
    WeaponUnarmed   = 24,  // induced from Fencing(2)
    Herbalism       = 25,
    Reading         = 26,
    Tailoring       = 27,  // hidden
    Armourer        = 28,  // hidden
    Weaponsmithing  = 29,  // hidden
    Shoemaking      = 30,  // hidden
    Gambling        = 31,  // hidden
    Houndmaster     = 32,

    Count           = 33,  // == array size m_skillLevels[33] / skillPoints[33];
                           // also the S_PerkDefinition::skillSelector "none / main level" value (0x21)
};

}  // namespace wh::rpgmodule
