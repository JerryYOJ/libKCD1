#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "text"  row_size: 12
// Registration: 0x1801060e0
#pragma pack(push, 1)
struct S_TextTableRow_3 {
    uint8_t _rowbase[4];  // 0x000
    int32_t text_id;  // 0x004  // PK
    // int32_t page_spread_number;  // 0x004 (alias)  // PK
    int32_t topic_id;  // 0x008
};
#pragma pack(pop)
static_assert(sizeof(S_TextTableRow_3) == 12, "Size mismatch for S_TextTableRow_3");

}  // namespace wh::databasemodule
