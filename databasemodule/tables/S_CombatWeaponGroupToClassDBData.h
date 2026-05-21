#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "combat_weapon_group"  row_size: 8
// Registration: 0x1800d8f20
#pragma pack(push, 1)
struct S_CombatWeaponGroupToClassDBData {
    uint8_t _rowbase[4];  // 0x000
    int32_t combat_weapon_group_id;  // 0x004  // PK
    // int32_t weapon_class_id;  // 0x004 (alias)  // PK
};
#pragma pack(pop)
static_assert(sizeof(S_CombatWeaponGroupToClassDBData) == 8, "Size mismatch for S_CombatWeaponGroupToClassDBData");

}  // namespace wh::databasemodule
