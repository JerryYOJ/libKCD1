#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "item"  row_size: 28
// Registration: 0x180108060
#pragma pack(push, 1)
struct S_ItemTableRow_14 {
    uint8_t _rowbase[16];  // 0x000
    uint64_t item_id;  // 0x010  // PK
    // const char* item_name;  // 0x010 (alias)
    int32_t item_category_id;  // 0x018
};
#pragma pack(pop)
static_assert(sizeof(S_ItemTableRow_14) == 28, "Size mismatch for S_ItemTableRow_14");

}  // namespace wh::databasemodule
