#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "src_combat_zone"  row_size: 24
// Registration: 0x1800d98c0
#pragma pack(push, 1)
struct S_CombatZoneDistanceDBData {
    uint8_t _rowbase[4];  // 0x000
    int32_t src_combat_zone_id;  // 0x004  // PK
    // int32_t dst_combat_zone_id;  // 0x004 (alias)  // PK
    float rpg_distance;  // 0x008
    float combat_distance;  // 0x00C
    float visual_guard_distance;  // 0x010
    float defense_guard_distance;  // 0x014
};
#pragma pack(pop)
static_assert(sizeof(S_CombatZoneDistanceDBData) == 24, "Size mismatch for S_CombatZoneDistanceDBData");

}  // namespace wh::databasemodule
