#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "combat_ui_rules"  row_size: 12
// Registration: 0x1800d8800
#pragma pack(push, 1)
struct S_CombatUIRulesDBData {
    uint8_t _rowbase[4];  // 0x000
    int32_t combat_ui_rules_id;  // 0x004  // PK
    // int32_t combat_end_guard_type_id;  // 0x004 (alias)
    int32_t combat_ui_rule;  // 0x008
};
#pragma pack(pop)
static_assert(sizeof(S_CombatUIRulesDBData) == 12, "Size mismatch for S_CombatUIRulesDBData");

}  // namespace wh::databasemodule
