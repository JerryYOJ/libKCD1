#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "combat_action_type"  row_size: 16
// Registration: 0x1800d2250
#pragma pack(push, 1)
struct S_CombatActionTypeTableRow {
    uint8_t _rowbase[4];  // 0x000
    int32_t combat_action_type_id;  // 0x004  // PK
    const char* combat_action_type_name;  // 0x008
};
#pragma pack(pop)
static_assert(sizeof(S_CombatActionTypeTableRow) == 16, "Size mismatch for S_CombatActionTypeTableRow");

}  // namespace wh::databasemodule
