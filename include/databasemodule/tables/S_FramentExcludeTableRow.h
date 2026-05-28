#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "ai_fragment_exclude"  row_size: 16
// Registration: 0x1800ddcd0
#pragma pack(push, 1)
struct S_FramentExcludeTableRow {
    uint8_t _rowbase[4];  // 0x000
    int32_t ai_fragment_exclude_id;  // 0x004  // PK
    const char* ai_fragment_exclude_prefix;  // 0x008
};
#pragma pack(pop)
static_assert(sizeof(S_FramentExcludeTableRow) == 16, "Size mismatch for S_FramentExcludeTableRow");

}  // namespace wh::databasemodule
