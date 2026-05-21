#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "race"  row_size: 16
// Registration: 0x1800f9730
#pragma pack(push, 1)
struct S_RaceTableRow {
    uint8_t _rowbase[4];  // 0x000
    int32_t race_id;  // 0x004  // PK
    const char* race_name;  // 0x008
};
#pragma pack(pop)
static_assert(sizeof(S_RaceTableRow) == 16, "Size mismatch for S_RaceTableRow");

}  // namespace wh::databasemodule
