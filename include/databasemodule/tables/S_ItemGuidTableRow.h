#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "item_guid"  row_size: 24
// Registration: 0x1800fc850
#pragma pack(push, 1)
struct S_ItemGuidTableRow {
    uint8_t _rowbase[16];  // 0x000
    uint64_t item_guid;  // 0x010  // PK
};
#pragma pack(pop)
static_assert(sizeof(S_ItemGuidTableRow) == 24, "Size mismatch for S_ItemGuidTableRow");

}  // namespace wh::databasemodule
