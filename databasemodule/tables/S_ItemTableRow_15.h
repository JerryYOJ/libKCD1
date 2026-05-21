#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "item"  row_size: 24
// Registration: 0x1801087d0
#pragma pack(push, 1)
struct S_ItemTableRow_15 {
    uint8_t _rowbase[16];  // 0x000
    uint64_t item_id;  // 0x010  // PK
    // int32_t key_type_id;  // 0x010 (alias)
    // int32_t key_subtype_id;  // 0x014 (alias)
};
#pragma pack(pop)
static_assert(sizeof(S_ItemTableRow_15) == 24, "Size mismatch for S_ItemTableRow_15");

}  // namespace wh::databasemodule
