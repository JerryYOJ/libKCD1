#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "structure"  row_size: 32
// Registration: 0x180148160
#pragma pack(push, 1)
struct S_NewHomesStructure {
    uint8_t _rowbase[4];  // 0x000
    int32_t structure_id;  // 0x004  // PK
    const char* structure_name;  // 0x008
    int32_t parcel_id;  // 0x010
    int32_t ui_order;  // 0x014
    int32_t default_tier;  // 0x018
    int32_t bookmark_group;  // 0x01C
};
#pragma pack(pop)
static_assert(sizeof(S_NewHomesStructure) == 32, "Size mismatch for S_NewHomesStructure");

}  // namespace wh::databasemodule
