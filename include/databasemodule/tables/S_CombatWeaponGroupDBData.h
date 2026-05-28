#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "combat_weapon_group"  row_size: 28
// Registration: 0x1800d8b10
#pragma pack(push, 1)
struct S_CombatWeaponGroupDBData {
    uint8_t _rowbase[4];  // 0x000
    int32_t combat_weapon_group_id;  // 0x004  // PK
    const char* combat_weapon_group_name;  // 0x008
    const char* mn_tag;  // 0x010
    int32_t combat_priority;  // 0x018
};
#pragma pack(pop)
static_assert(sizeof(S_CombatWeaponGroupDBData) == 28, "Size mismatch for S_CombatWeaponGroupDBData");

}  // namespace wh::databasemodule
