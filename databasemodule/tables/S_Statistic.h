#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "statistic"  row_size: 72
// Registration: 0x180124f20
#pragma pack(push, 1)
struct S_Statistic {
    uint8_t _rowbase[4];  // 0x000
    int32_t statistic_id;  // 0x004  // PK
    // int32_t statistic_group_id;  // 0x004 (alias)
    const char* statistic_name;  // 0x008
    const char* ui_name;  // 0x010
    const char* ui_desc;  // 0x018
    const char* type;  // 0x020
    uint8_t _pad_0x028[4];
    int32_t ui_order;  // 0x02C
    bool is_global;  // 0x030
    uint8_t _pad_0x031[3];
    int32_t psn_id;  // 0x034
    int32_t statistic_unit_id;  // 0x038
    uint8_t _pad_0x03C[4];
    const char* xboxlive_id;  // 0x040
};
#pragma pack(pop)
static_assert(sizeof(S_Statistic) == 72, "Size mismatch for S_Statistic");

}  // namespace wh::databasemodule
