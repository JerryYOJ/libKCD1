#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "text"  row_size: 16
// Registration: 0x1801057f0
#pragma pack(push, 1)
struct S_TextTableRow_2 {
    uint8_t _rowbase[4];  // 0x000
    int32_t text_id;  // 0x004  // PK
    // int32_t page;  // 0x004 (alias)  // PK
    const char* image;  // 0x008
};
#pragma pack(pop)
static_assert(sizeof(S_TextTableRow_2) == 16, "Size mismatch for S_TextTableRow_2");

}  // namespace wh::databasemodule
