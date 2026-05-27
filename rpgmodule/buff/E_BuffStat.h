#pragma once
#include <cstdint>

namespace wh::rpgmodule {

// Base soul stats (modifier category 0, 10 entries)
// Enum registry at vtable+0x50, sentinel = 0xA
enum class E_SoulStat : int32_t {
    Strength   = 0,   // str
    Agility    = 1,   // agi
    Vitality   = 2,   // vit
    Speech     = 3,   // spc
    Visibility = 4,   // vis
    Hearing    = 5,   // hea
    Charisma   = 6,   // bar (barter/charisma)
    Courage    = 7,   // cou
    Reputation = 8,   // rep
    Progress   = 9,   // prg
    Count      = 10
};

// Soul-level modifiers (modifier category 6, 6 entries)
// Enum registry at vtable+0x40, sentinel = 6
enum class E_SoulLevel : int32_t {
    Health     = 0,
    Stamina    = 1,
    Exhaust    = 2,
    Hunger     = 3,
    Karma      = 4,
    Alcoholism = 5,
    Count      = 6
};

// Movement type modifiers (modifier category 4, 6 entries)
// Enum registry via sub_180584920
enum class E_MovementType : int32_t {
    Stand       = 0,
    Walk        = 1,
    Run         = 2,
    Sprint      = 3,
    HorseSprint = 4,
    HorseDash   = 5,
    Count       = 6
};

// Buff class — determines which modifier dispatch path is used in ProcessModifiers.
// Read from C_BuffData+0x2C.
// Switch at 0x18044921C.
enum class E_BuffClass : int32_t {
    General    = 0,
    StatSkill  = 1,   // sub_180A8C4D0: skill/stat modifiers
    Derived    = 3,   // sub_180A8C5F0: derived stat modifiers
    Perception = 4,   // sub_180A8C570: perception modifiers
};

}  // namespace wh::rpgmodule
