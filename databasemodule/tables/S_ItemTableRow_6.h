#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "item"  row_size: 32
// Registration: 0x180104230
#pragma pack(push, 1)
struct S_ItemTableRow_6 {
    uint8_t _rowbase[16];  // 0x000
    uint64_t item_id;  // 0x010  // PK
    // CryGUID buff_id;  // 0x010 (alias)
    uint8_t _pad_0x018[8];
};
#pragma pack(pop)
static_assert(sizeof(S_ItemTableRow_6) == 32, "Size mismatch for S_ItemTableRow_6");

}  // namespace wh::databasemodule
