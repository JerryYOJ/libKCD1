#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "combat_zone"  row_size: 8
// Registration: 0x1800b06b0
#pragma pack(push, 1)
struct S_CombatZoneTableRow {
    uint8_t _rowbase[4];  // 0x000
    int32_t combat_zone_id;  // 0x004  // PK
    // int32_t combat_tag_id;  // 0x004 (alias)  // PK
};
#pragma pack(pop)
static_assert(sizeof(S_CombatZoneTableRow) == 8, "Size mismatch for S_CombatZoneTableRow");

}  // namespace wh::databasemodule
