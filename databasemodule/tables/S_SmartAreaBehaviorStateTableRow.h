#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "smart_area_behavior_state"  row_size: 16
// Registration: 0x1801db2b0
#pragma pack(push, 1)
struct S_SmartAreaBehaviorStateTableRow {
    uint8_t _rowbase[4];  // 0x000
    int32_t smart_area_behavior_state_id;  // 0x004  // PK
    const char* smart_area_behavior_state_name;  // 0x008
};
#pragma pack(pop)
static_assert(sizeof(S_SmartAreaBehaviorStateTableRow) == 16, "Size mismatch for S_SmartAreaBehaviorStateTableRow");

}  // namespace wh::databasemodule
