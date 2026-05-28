#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "hobby"  row_size: 24
// Registration: 0x180137e00
#pragma pack(push, 1)
struct S_HobbyTableRow {
    uint8_t _rowbase[4];  // 0x000
    int32_t hobby_id;  // 0x004  // PK
    uint8_t _pad_0x008[8];
    uint64_t soul_id;  // 0x010  // PK
    // float mass;  // 0x014 (alias)
};
#pragma pack(pop)
static_assert(sizeof(S_HobbyTableRow) == 24, "Size mismatch for S_HobbyTableRow");

}  // namespace wh::databasemodule
