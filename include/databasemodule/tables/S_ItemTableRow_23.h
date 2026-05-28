#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "item"  row_size: 40
// Registration: 0x18010aae0
#pragma pack(push, 1)
struct S_ItemTableRow_23 {
    uint8_t _rowbase[16];  // 0x000
    uint64_t item_id;  // 0x010  // PK
    // int32_t icon_id;  // 0x010 (alias)
    const char* ui_name;  // 0x018
    const char* ui_info;  // 0x020
};
#pragma pack(pop)
static_assert(sizeof(S_ItemTableRow_23) == 40, "Size mismatch for S_ItemTableRow_23");

}  // namespace wh::databasemodule
