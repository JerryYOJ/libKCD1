#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "location_category"  row_size: 8
// Registration: 0x18011ac40
#pragma pack(push, 1)
struct S_LocationCategory {
    uint8_t _rowbase[4];  // 0x000
    int32_t location_category_id;  // 0x004  // PK
};
#pragma pack(pop)
static_assert(sizeof(S_LocationCategory) == 8, "Size mismatch for S_LocationCategory");

}  // namespace wh::databasemodule
