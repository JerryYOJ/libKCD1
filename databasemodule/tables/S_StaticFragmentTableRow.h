#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "option_index"  row_size: 16
// Registration: 0x1800ddf00
#pragma pack(push, 1)
struct S_StaticFragmentTableRow {
    uint8_t _rowbase[4];  // 0x000
    int32_t option_index;  // 0x004  // PK
    const char* actor_class;  // 0x008  // PK
    // const char* fragment;  // 0x008 (alias)  // PK
    // const char* tags;  // 0x008 (alias)  // PK
    // --- virtual columns (offset=-1, not in struct memory) ---
    // int32_t mn_fragment_id;
};
#pragma pack(pop)
static_assert(sizeof(S_StaticFragmentTableRow) == 16, "Size mismatch for S_StaticFragmentTableRow");

}  // namespace wh::databasemodule
