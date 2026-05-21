#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "combat_action_type_group"  row_size: 8
// Registration: 0x1800d2020
#pragma pack(push, 1)
struct S_CombatActionTypeGroupDBData {
    uint8_t _rowbase[4];  // 0x000
    int32_t combat_action_type_group_id;  // 0x004  // PK
    // int32_t combat_action_type_id;  // 0x004 (alias)  // PK
};
#pragma pack(pop)
static_assert(sizeof(S_CombatActionTypeGroupDBData) == 8, "Size mismatch for S_CombatActionTypeGroupDBData");

}  // namespace wh::databasemodule
