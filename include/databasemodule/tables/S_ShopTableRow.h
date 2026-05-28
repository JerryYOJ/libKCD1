#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "shop"  row_size: 28
// Registration: 0x1801594c0
#pragma pack(push, 1)
struct S_ShopTableRow {
    uint8_t _rowbase[4];  // 0x000
    int32_t shop_id;  // 0x004  // PK
    // int32_t shop_type_id;  // 0x004 (alias)  // PK
    uint8_t _pad_0x008[8];
    uint64_t item_id;  // 0x010  // PK
    float amount_multiplier;  // 0x018
};
#pragma pack(pop)
static_assert(sizeof(S_ShopTableRow) == 28, "Size mismatch for S_ShopTableRow");

}  // namespace wh::databasemodule
