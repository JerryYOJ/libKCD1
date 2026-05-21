#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "statistic_group"  row_size: 32
// Registration: 0x1801259d0
#pragma pack(push, 1)
struct S_StatisticGroup {
    uint8_t _rowbase[4];  // 0x000
    int32_t statistic_group_id;  // 0x004  // PK
    const char* statistic_group_name;  // 0x008
    const char* ui_name;  // 0x010
    int32_t icon_id;  // 0x018
    int32_t ui_order;  // 0x01C
};
#pragma pack(pop)
static_assert(sizeof(S_StatisticGroup) == 32, "Size mismatch for S_StatisticGroup");

}  // namespace wh::databasemodule
