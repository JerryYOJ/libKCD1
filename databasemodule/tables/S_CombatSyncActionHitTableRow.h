#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "mn_fragment"  row_size: 16
// Registration: 0x1800d81f0
#pragma pack(push, 1)
struct S_CombatSyncActionHitTableRow {
    uint8_t _rowbase[4];  // 0x000
    int32_t mn_fragment_id;  // 0x004  // PK
    // int32_t order;  // 0x004 (alias)  // PK
    uint8_t _pad_0x008[4];
    float attack_value_coef;  // 0x00C
};
#pragma pack(pop)
static_assert(sizeof(S_CombatSyncActionHitTableRow) == 16, "Size mismatch for S_CombatSyncActionHitTableRow");

}  // namespace wh::databasemodule
