#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "combat_input_class"  row_size: 24
// Registration: 0x1800d66e0
#pragma pack(push, 1)
struct S_CombatInputClassTableRow {
    uint8_t _rowbase[4];  // 0x000
    int32_t combat_input_class_id;  // 0x004  // PK
    const char* combat_input_class_name;  // 0x008
    const char* mn_tag;  // 0x010
};
#pragma pack(pop)
static_assert(sizeof(S_CombatInputClassTableRow) == 24, "Size mismatch for S_CombatInputClassTableRow");

}  // namespace wh::databasemodule
