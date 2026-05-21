#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "combat_tag"  row_size: 16
// Registration: 0x1800d85d0
#pragma pack(push, 1)
struct S_CombatTagTableRow {
    uint8_t _rowbase[4];  // 0x000
    int32_t combat_tag_id;  // 0x004  // PK
    const char* combat_tag_name;  // 0x008
};
#pragma pack(pop)
static_assert(sizeof(S_CombatTagTableRow) == 16, "Size mismatch for S_CombatTagTableRow");

}  // namespace wh::databasemodule
