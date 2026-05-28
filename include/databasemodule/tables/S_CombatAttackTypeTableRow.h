#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "combat_attack_type"  row_size: 8
// Registration: 0x1800b0480
#pragma pack(push, 1)
struct S_CombatAttackTypeTableRow {
    uint8_t _rowbase[4];  // 0x000
    int32_t combat_attack_type_id;  // 0x004  // PK
    // int32_t combat_tag_id;  // 0x004 (alias)  // PK
};
#pragma pack(pop)
static_assert(sizeof(S_CombatAttackTypeTableRow) == 8, "Size mismatch for S_CombatAttackTypeTableRow");

}  // namespace wh::databasemodule
