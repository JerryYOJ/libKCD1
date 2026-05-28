#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "item"  row_size: 64
// Registration: 0x180104480
#pragma pack(push, 1)
struct S_ItemTableRow_7 {
    uint8_t _rowbase[16];  // 0x000
    uint64_t item_id;  // 0x010  // PK
    // float side_weight_1;  // 0x010 (alias)
    // float side_weight_2;  // 0x014 (alias)
    float side_weight_3;  // 0x018
    float side_weight_4;  // 0x01C
    float side_weight_5;  // 0x020
    float side_weight_6;  // 0x024
    int32_t side_value_1;  // 0x028
    int32_t side_value_2;  // 0x02C
    int32_t side_value_3;  // 0x030
    int32_t side_value_4;  // 0x034
    int32_t side_value_5;  // 0x038
    int32_t side_value_6;  // 0x03C
};
#pragma pack(pop)
static_assert(sizeof(S_ItemTableRow_7) == 64, "Size mismatch for S_ItemTableRow_7");

}  // namespace wh::databasemodule
