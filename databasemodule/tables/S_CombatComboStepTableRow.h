#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "combat_combo"  row_size: 20
// Registration: 0x1800d35b0
#pragma pack(push, 1)
struct S_CombatComboStepTableRow {
    uint8_t _rowbase[4];  // 0x000
    int32_t combat_combo_id;  // 0x004  // PK
    // int32_t step;  // 0x004 (alias)  // PK
    uint8_t _pad_0x008[4];
    int32_t atk_combat_zone_id;  // 0x00C
    int32_t attack_type_id;  // 0x010
};
#pragma pack(pop)
static_assert(sizeof(S_CombatComboStepTableRow) == 20, "Size mismatch for S_CombatComboStepTableRow");

}  // namespace wh::databasemodule
