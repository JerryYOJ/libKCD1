#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "item"  row_size: 40
// Registration: 0x180105080
#pragma pack(push, 1)
struct S_ItemTableRow_8 {
    uint8_t _rowbase[16];  // 0x000
    uint64_t item_id;  // 0x010  // PK
    // bool is_divisible;  // 0x010 (alias)
    const char* container_model;  // 0x018
    const char* container_material;  // 0x020
};
#pragma pack(pop)
static_assert(sizeof(S_ItemTableRow_8) == 40, "Size mismatch for S_ItemTableRow_8");

}  // namespace wh::databasemodule
