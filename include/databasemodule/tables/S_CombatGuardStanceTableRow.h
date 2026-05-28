#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "combat_guard_stance"  row_size: 32
// Registration: 0x1800d4480
#pragma pack(push, 1)
struct S_CombatGuardStanceTableRow {
    uint8_t _rowbase[4];  // 0x000
    int32_t combat_guard_stance_id;  // 0x004  // PK
    const char* combat_guard_stance_name;  // 0x008
    const char* mn_tag;  // 0x010
    const char* opp_mn_tag;  // 0x018
};
#pragma pack(pop)
static_assert(sizeof(S_CombatGuardStanceTableRow) == 32, "Size mismatch for S_CombatGuardStanceTableRow");

}  // namespace wh::databasemodule
