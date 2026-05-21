#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "combat_guard_stance"  row_size: 24
// Registration: 0x1800d6a00
#pragma pack(push, 1)
struct S_CombatNativeGuardZoneTableRow {
    uint8_t _rowbase[4];  // 0x000
    int32_t combat_guard_stance_id;  // 0x004  // PK
    // int32_t combat_zone_id;  // 0x004 (alias)  // PK
    // int32_t r_weapon_class_id;  // 0x004 (alias)  // PK
    // int32_t l_weapon_class_id;  // 0x004 (alias)  // PK
    uint8_t _pad_0x008[8];
    int32_t r_combat_weapon_group_id;  // 0x010
    int32_t l_combat_weapon_group_id;  // 0x014
};
#pragma pack(pop)
static_assert(sizeof(S_CombatNativeGuardZoneTableRow) == 24, "Size mismatch for S_CombatNativeGuardZoneTableRow");

}  // namespace wh::databasemodule
