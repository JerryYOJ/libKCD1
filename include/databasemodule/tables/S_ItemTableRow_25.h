#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "item"  row_size: 24
// Registration: 0x18010b160
#pragma pack(push, 1)
struct S_ItemTableRow_25 {
    uint8_t _rowbase[16];  // 0x000
    uint64_t item_id;  // 0x010  // PK
    // bool is_quest;  // 0x010 (alias)
};
#pragma pack(pop)
static_assert(sizeof(S_ItemTableRow_25) == 24, "Size mismatch for S_ItemTableRow_25");

}  // namespace wh::databasemodule
