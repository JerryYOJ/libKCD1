#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "order"  row_size: 32
// Registration: 0x1801083a0
#pragma pack(push, 1)
struct S_OrderTableRow {
    uint8_t _rowbase[4];  // 0x000
    int32_t order;  // 0x004  // PK
    uint8_t _pad_0x008[8];
    uint64_t item_id;  // 0x010  // PK
    // const char* model;  // 0x010 (alias)
    const char* material;  // 0x018
};
#pragma pack(pop)
static_assert(sizeof(S_OrderTableRow) == 32, "Size mismatch for S_OrderTableRow");

}  // namespace wh::databasemodule
