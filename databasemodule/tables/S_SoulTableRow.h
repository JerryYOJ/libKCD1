#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "soul"  row_size: 24
// Registration: 0x180138140
#pragma pack(push, 1)
struct S_SoulTableRow {
    uint8_t _rowbase[16];  // 0x000
    uint64_t soul_id;  // 0x010  // PK
    // uint64_t perk_id;  // 0x010 (alias)  // PK
};
#pragma pack(pop)
static_assert(sizeof(S_SoulTableRow) == 24, "Size mismatch for S_SoulTableRow");

}  // namespace wh::databasemodule
