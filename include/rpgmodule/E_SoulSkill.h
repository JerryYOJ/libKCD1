#pragma once
#include <cstdint>

namespace wh::rpgmodule {

// ---------------------------------------------------------------------------
// E_SoulSkill -- skill ids (rpg/skill.xml, 33 rows). Modifier category 1
// (C_Soul m_skillMods). Loaded into C_SkillDatabase by sub_180727E3C; the
// code->id lookup is C_RPGUtils vtable +0x70 (SkillNameToId, not-found sentinel
// 0x21 = 33). Enumerator names are the verbatim skill_name values.
// (fencing(2)/defense(15) are the two skills that feed the combat reaction calc.)
// ---------------------------------------------------------------------------
enum class E_SoulSkill : int32_t {
    Stealth        = 0,
    HorseRiding    = 1,
    Fencing        = 2,    // melee weapon-handling skill (skill-diff term)
    Bard           = 3,
    Lockpicking    = 4,
    Pickpocketing  = 5,
    Alchemy        = 6,
    Cooking        = 7,
    Repairing      = 8,
    Smithing       = 9,
    Fishing        = 10,
    Mining         = 11,
    FirstAid       = 12,
    Drinking       = 13,
    Hunter         = 14,
    Defense        = 15,   // defensive skill (perfect-block base)
    WeaponSword    = 16,
    WeaponAxe      = 17,
    WeaponBow      = 18,
    WeaponCrossbow = 19,
    WeaponShield   = 20,
    WeaponMace     = 21,
    WeaponDagger   = 22,
    WeaponLarge    = 23,
    WeaponUnarmed  = 24,
    Herbalism      = 25,
    Reading        = 26,
    Tailoring      = 27,
    Armourer       = 28,
    Weaponsmithing = 29,
    Shoemaking     = 30,
    Gambling       = 31,
    Houndmaster    = 32,
    Count          = 33,
};

}  // namespace wh::rpgmodule
