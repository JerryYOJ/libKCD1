#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "combat_attack_type"  row_size: 8
// Registration: 0x1800d4080
#pragma pack(push, 1)
struct S_CombatDamageTypeMappingDBData {
    uint8_t _rowbase[4];  // 0x000
    int32_t combat_attack_type_id;  // 0x004  // PK
    // int32_t rpg_damage_type_id;  // 0x004 (alias)  // PK
    // int32_t r_weapon_class_id;  // 0x004 (alias)  // PK
    // int32_t r_weapon_sub_class_id;  // 0x004 (alias)  // PK
};
#pragma pack(pop)
static_assert(sizeof(S_CombatDamageTypeMappingDBData) == 8, "Size mismatch for S_CombatDamageTypeMappingDBData");

}  // namespace wh::databasemodule
