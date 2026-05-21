#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "combat_hit_origin"  row_size: 32
// Registration: 0x1800d5eb0
#pragma pack(push, 1)
struct S_CombatHitOriginDBData {
    uint8_t _rowbase[4];  // 0x000
    int32_t combat_hit_origin_id;  // 0x004  // PK
    const char* combat_hit_origin_name;  // 0x008
    const char* mn_tag;  // 0x010
    float angle_from;  // 0x018
    float angle_to;  // 0x01C
};
#pragma pack(pop)
static_assert(sizeof(S_CombatHitOriginDBData) == 32, "Size mismatch for S_CombatHitOriginDBData");

}  // namespace wh::databasemodule
