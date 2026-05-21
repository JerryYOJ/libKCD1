#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "skin"  row_size: 32
// Registration: 0x1800f3a90
#pragma pack(push, 1)
struct S_RaycastClothingRow {
    uint8_t _rowbase[8];  // 0x000
    const char* skin;  // 0x008  // PK
    // const char* material;  // 0x008 (alias)  // PK
    const char* opaque_triangle_mask;  // 0x010
    const char* not_culled_triangle_mask;  // 0x018
};
#pragma pack(pop)
static_assert(sizeof(S_RaycastClothingRow) == 32, "Size mismatch for S_RaycastClothingRow");

}  // namespace wh::databasemodule
