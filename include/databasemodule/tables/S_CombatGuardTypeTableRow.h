#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "combat_guard_type"  row_size: 33
// Registration: 0x1800d59a0
#pragma pack(push, 1)
struct S_CombatGuardTypeTableRow {
    uint8_t _rowbase[4];  // 0x000
    int32_t combat_guard_type_id;  // 0x004  // PK
    const char* combat_guard_type_name;  // 0x008
    const char* mn_tag;  // 0x010
    const char* end_mn_tag;  // 0x018
    bool move_restriction;  // 0x020
};
#pragma pack(pop)
static_assert(sizeof(S_CombatGuardTypeTableRow) == 33, "Size mismatch for S_CombatGuardTypeTableRow");

}  // namespace wh::databasemodule
