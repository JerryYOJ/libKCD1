#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "item"  row_size: 24
// Registration: 0x180101a50
#pragma pack(push, 1)
struct S_ItemTableRow_2 {
    uint8_t _rowbase[16];  // 0x000
    uint64_t item_id;  // 0x010  // PK
    // const char* ui_name;  // 0x010 (alias)
};
#pragma pack(pop)
static_assert(sizeof(S_ItemTableRow_2) == 24, "Size mismatch for S_ItemTableRow_2");

}  // namespace wh::databasemodule
