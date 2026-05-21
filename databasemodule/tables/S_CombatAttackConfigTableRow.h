#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "combat_attack_config"  row_size: 28
// Registration: 0x1800d2480
#pragma pack(push, 1)
struct S_CombatAttackConfigTableRow {
    uint8_t _rowbase[4];  // 0x000
    int32_t combat_attack_config_id;  // 0x004  // PK
    // int32_t combat_zone_id;  // 0x004 (alias)
    int32_t combat_input_class_id;  // 0x008
    int32_t r_weapon_class_id;  // 0x00C
    int32_t l_weapon_class_id;  // 0x010
    int32_t r_combat_weapon_group_id;  // 0x014
    int32_t l_combat_weapon_group_id;  // 0x018
};
#pragma pack(pop)
static_assert(sizeof(S_CombatAttackConfigTableRow) == 28, "Size mismatch for S_CombatAttackConfigTableRow");

}  // namespace wh::databasemodule
