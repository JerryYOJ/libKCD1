#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "combat_zone"  row_size: 77
// Registration: 0x1800d9ec0
#pragma pack(push, 1)
struct S_CombatZoneTableRow_2 {
    uint8_t _rowbase[4];  // 0x000
    int32_t combat_zone_id;  // 0x004  // PK
    const char* combat_zone_name;  // 0x008
    const char* attack_mn_tag;  // 0x010
    const char* defense_mn_tag;  // 0x018
    const char* start_mn_tag;  // 0x020
    const char* end_mn_tag;  // 0x028
    const char* riposte_mn_tag;  // 0x030
    float radius_from;  // 0x038
    float radius_to;  // 0x03C
    float angle_from;  // 0x040
    float angle_to;  // 0x044
    int32_t cursor_idx;  // 0x048
    bool default_zone;  // 0x04C
};
#pragma pack(pop)
static_assert(sizeof(S_CombatZoneTableRow_2) == 77, "Size mismatch for S_CombatZoneTableRow_2");

}  // namespace wh::databasemodule
