#pragma once
#include <cstdint>

namespace wh::rpgmodule {

// Modifier-list category (index into C_Soul's 7 sorted modifier lists, and into the matching
// 7 staging lists on C_SoulBuffInstance). Each category has its OWN target-id namespace +
// code->id registry; DispatchModifier (sub_1802AD9B0) resolves a buff param's code against the
// registries in turn and the first match sets both the category and the id. See S_ModifierNode
// for the per-category target-id enum (the template's T).
enum class E_ModifierCategory : int32_t {
    Stat        = 0,   // base soul stats        -> E_SoulStat       (10; C_RPGUtils code->id vtbl+0x50)
    Skill       = 1,   // skills                 -> E_SoulSkill      (33; vtbl+0x70, from rpg/skill.xml)
    DerivedStat = 2,   // combat/automation stats-> E_CombatStat     (39; vtbl+0x88) -- the reaction-weight hook
    Detail      = 3,   // character derived stats-> E_DerivedStat    (110; vtbl+0x58)
    Movement    = 4,   // movement-type mods     -> E_MovementType   (6)
    Special     = 5,   // special / manual       -> (no code registry; ids set in C++)
    SoulLevel   = 6,   // soul-level mods        -> E_SoulLevel      (6; vtbl+0x40)
    Count       = 7,
};

}  // namespace wh::rpgmodule
