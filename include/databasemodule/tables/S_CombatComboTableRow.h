#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "combat_combo"  row_size: 40
// Registration: 0x1800d3a30
#pragma pack(push, 1)
struct S_CombatComboTableRow {
    uint8_t _rowbase[4];  // 0x000
    int32_t combat_combo_id;  // 0x004  // PK
    const char* combat_combo_strid;  // 0x008
    const char* combat_combo_name;  // 0x010
    int32_t atk_r_weapon_class_id;  // 0x018
    int32_t atk_l_weapon_class_id;  // 0x01C
    int32_t atk_r_weapon_group_id;  // 0x020
    int32_t atk_l_weapon_group_id;  // 0x024
};
#pragma pack(pop)
static_assert(sizeof(S_CombatComboTableRow) == 40, "Size mismatch for S_CombatComboTableRow");

}  // namespace wh::databasemodule
