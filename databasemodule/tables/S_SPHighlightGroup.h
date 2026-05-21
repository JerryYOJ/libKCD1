#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "sph_group"  row_size: 16
// Registration: 0x18012ba10
#pragma pack(push, 1)
struct S_SPHighlightGroup {
    uint8_t _rowbase[4];  // 0x000
    int32_t sph_group_id;  // 0x004  // PK
    const char* sph_group_ui_name;  // 0x008
};
#pragma pack(pop)
static_assert(sizeof(S_SPHighlightGroup) == 16, "Size mismatch for S_SPHighlightGroup");

}  // namespace wh::databasemodule
