#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "item"  row_size: 24
// Registration: 0x180107630
#pragma pack(push, 1)
struct S_ItemTableRow_12 {
    uint8_t _rowbase[16];  // 0x000
    uint64_t item_id;  // 0x010  // PK
    // int32_t visor_type_id;  // 0x010 (alias)
};
#pragma pack(pop)
static_assert(sizeof(S_ItemTableRow_12) == 24, "Size mismatch for S_ItemTableRow_12");

}  // namespace wh::databasemodule
