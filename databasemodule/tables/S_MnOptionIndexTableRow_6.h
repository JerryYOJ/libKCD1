#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "mn_option_index"  row_size: 16
// Registration: 0x1800f07e0
#pragma pack(push, 1)
struct S_MnOptionIndexTableRow_6 {
    uint8_t _rowbase[4];  // 0x000
    float offset;  // 0x004
    // int32_t mn_option_index;  // 0x004 (alias)  // PK
    float align;  // 0x008
    // const char* mn_fragment_id;  // 0x008 (alias)  // PK
    // const char* mn_tags;  // 0x008 (alias)  // PK
    int32_t actor_class_hash;  // 0x00C
    // --- virtual columns (offset=-1, not in struct memory) ---
    // float height;
};
#pragma pack(pop)
static_assert(sizeof(S_MnOptionIndexTableRow_6) == 16, "Size mismatch for S_MnOptionIndexTableRow_6");

}  // namespace wh::databasemodule
