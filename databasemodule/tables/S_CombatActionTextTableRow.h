#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "combat_action_type"  row_size: 24
// Registration: 0x1800d1710
#pragma pack(push, 1)
struct S_CombatActionTextTableRow {
    uint8_t _rowbase[4];  // 0x000
    int32_t combat_action_type_id;  // 0x004  // PK
    // int32_t combat_input_class_id;  // 0x004 (alias)  // PK
    // int32_t combat_guard_type_id;  // 0x004 (alias)  // PK
    uint8_t _pad_0x008[8];
    const char* string_name;  // 0x010
};
#pragma pack(pop)
static_assert(sizeof(S_CombatActionTextTableRow) == 24, "Size mismatch for S_CombatActionTextTableRow");

}  // namespace wh::databasemodule
