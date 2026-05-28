#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "location"  row_size: 24
// Registration: 0x18011aa10
#pragma pack(push, 1)
struct S_LocationTableRow {
    uint8_t _rowbase[16];  // 0x000
    uint64_t location_id;  // 0x010  // PK
    // uint64_t perk_id;  // 0x010 (alias)  // PK
};
#pragma pack(pop)
static_assert(sizeof(S_LocationTableRow) == 24, "Size mismatch for S_LocationTableRow");

}  // namespace wh::databasemodule
