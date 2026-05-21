#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "situation_global_condition"  row_size: 52
// Registration: 0x1801d9120
#pragma pack(push, 1)
struct S_SituationGlobalConditionTableRow {
    uint8_t _rowbase[16];  // 0x000
    uint64_t situation_global_condition_id;  // 0x010  // PK
    // CryGUID situation_id;  // 0x010 (alias)
    uint8_t _pad_0x018[8];
    int32_t type;  // 0x020
    uint8_t _pad_0x024[4];
    const char* data;  // 0x028
    int32_t order_by;  // 0x030
};
#pragma pack(pop)
static_assert(sizeof(S_SituationGlobalConditionTableRow) == 52, "Size mismatch for S_SituationGlobalConditionTableRow");

}  // namespace wh::databasemodule
