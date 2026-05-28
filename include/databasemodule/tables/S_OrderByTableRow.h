#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "order_by"  row_size: 36
// Registration: 0x1801d65b0
#pragma pack(push, 1)
struct S_OrderByTableRow {
    uint8_t _rowbase[4];  // 0x000
    int32_t order_by;  // 0x004  // PK
    uint8_t _pad_0x008[8];
    uint64_t positioning_shape_id;  // 0x010  // PK
    // float location_x;  // 0x014 (alias)
    float location_y;  // 0x018
    float direction_x;  // 0x01C
    float direction_y;  // 0x020
};
#pragma pack(pop)
static_assert(sizeof(S_OrderByTableRow) == 36, "Size mismatch for S_OrderByTableRow");

}  // namespace wh::databasemodule
