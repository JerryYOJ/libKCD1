#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "combat_side"  row_size: 36
// Registration: 0x1800d7bf0
#pragma pack(push, 1)
struct S_CombatSideDBData {
    uint8_t _rowbase[4];  // 0x000
    int32_t combat_side_id;  // 0x004  // PK
    const char* combat_side_name;  // 0x008
    const char* mn_tag;  // 0x010
    float angle_from;  // 0x018
    float angle_to;  // 0x01C
    int32_t combat_action_type_id;  // 0x020
};
#pragma pack(pop)
static_assert(sizeof(S_CombatSideDBData) == 36, "Size mismatch for S_CombatSideDBData");

}  // namespace wh::databasemodule
