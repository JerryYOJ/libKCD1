#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "shop"  row_size: 52
// Registration: 0x1801598f0
#pragma pack(push, 1)
struct S_ShopTableRow_2 {
    uint8_t _rowbase[4];  // 0x000
    int32_t shop_id;  // 0x004  // PK
    // int32_t shop_type_id;  // 0x004 (alias)  // PK
    uint8_t _pad_0x008[4];
    float amount_multiplier;  // 0x00C
    float amount_multiplier_random_add;  // 0x010
    float price_buy_multiplier;  // 0x014
    float price_sell_multiplier;  // 0x018
    uint8_t _pad_0x01C[4];
    const char* shop_name;  // 0x020
    int32_t restock_day_mask;  // 0x028
    float business_hours_begin;  // 0x02C
    float business_hours_end;  // 0x030
};
#pragma pack(pop)
static_assert(sizeof(S_ShopTableRow_2) == 52, "Size mismatch for S_ShopTableRow_2");

}  // namespace wh::databasemodule
