#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "src_zone"  row_size: 24
// Registration: 0x1800d4890
#pragma pack(push, 1)
struct S_CombatZoneMappingTableRow {
    uint8_t _rowbase[4];  // 0x000
    int32_t src_zone_id;  // 0x004  // PK
    // int32_t dst_zone_id;  // 0x004 (alias)  // PK
    // int32_t combat_attack_type_id;  // 0x004 (alias)  // PK
    // int32_t weapon_class_id;  // 0x004 (alias)  // PK
    // int32_t combat_input_class_id;  // 0x004 (alias)  // PK
    uint8_t _pad_0x008[12];
    int32_t combat_action_type_id;  // 0x014
};
#pragma pack(pop)
static_assert(sizeof(S_CombatZoneMappingTableRow) == 24, "Size mismatch for S_CombatZoneMappingTableRow");

}  // namespace wh::databasemodule
