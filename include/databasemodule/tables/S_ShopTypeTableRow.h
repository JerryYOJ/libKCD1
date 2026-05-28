#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "shop_type"  row_size: 28
// Registration: 0x18015a360
#pragma pack(push, 1)
struct S_ShopTypeTableRow {
    uint8_t _rowbase[4];  // 0x000
    int32_t shop_type_id;  // 0x004  // PK
    uint8_t _pad_0x008[8];
    uint64_t item_id;  // 0x010  // PK
    // bool default_on;  // 0x014 (alias)
    float amount;  // 0x018
};
#pragma pack(pop)
static_assert(sizeof(S_ShopTypeTableRow) == 28, "Size mismatch for S_ShopTypeTableRow");

}  // namespace wh::databasemodule
