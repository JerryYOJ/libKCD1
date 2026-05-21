#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "subbrain"  row_size: 32
// Registration: 0x1801e0ef0
#pragma pack(push, 1)
struct S_SubbrainTableRow_8 {
    uint8_t _rowbase[16];  // 0x000
    uint64_t subbrain_id;  // 0x010  // PK
    // const char* file_name;  // 0x010 (alias)
    const char* tree_name;  // 0x018
};
#pragma pack(pop)
static_assert(sizeof(S_SubbrainTableRow_8) == 32, "Size mismatch for S_SubbrainTableRow_8");

}  // namespace wh::databasemodule
