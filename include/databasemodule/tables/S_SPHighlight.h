#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "sph_highlight"  row_size: 32
// Registration: 0x18012b280
#pragma pack(push, 1)
struct S_SPHighlight {
    uint8_t _rowbase[4];  // 0x000
    int32_t sph_highlight_id;  // 0x004  // PK
    int32_t type;  // 0x008
    int32_t significance;  // 0x00C
    bool default_interest;  // 0x010
    uint8_t _pad_0x011[3];
    int32_t start_delta;  // 0x014
    int32_t end_delta;  // 0x018
    int32_t sph_group_id;  // 0x01C
};
#pragma pack(pop)
static_assert(sizeof(S_SPHighlight) == 32, "Size mismatch for S_SPHighlight");

}  // namespace wh::databasemodule
