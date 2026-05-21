#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "item"  row_size: 24
// Registration: 0x180108ae0
#pragma pack(push, 1)
struct S_ItemTableRow_16 {
    uint8_t _rowbase[16];  // 0x000
    uint64_t item_id;  // 0x010  // PK
};
#pragma pack(pop)
static_assert(sizeof(S_ItemTableRow_16) == 24, "Size mismatch for S_ItemTableRow_16");

}  // namespace wh::databasemodule
