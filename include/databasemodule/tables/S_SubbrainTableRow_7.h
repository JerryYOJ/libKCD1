#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "subbrain"  row_size: 50
// Registration: 0x1801e0830
#pragma pack(push, 1)
struct S_SubbrainTableRow_7 {
    uint8_t _rowbase[16];  // 0x000
    uint64_t subbrain_id;  // 0x010  // PK
    // const char* file_name;  // 0x010 (alias)
    const char* on_request_tree;  // 0x018
    const char* on_release_tree;  // 0x020
    const char* on_update_tree;  // 0x028
    bool explicit_initialization;  // 0x030
    bool system_variables;  // 0x031
};
#pragma pack(pop)
static_assert(sizeof(S_SubbrainTableRow_7) == 50, "Size mismatch for S_SubbrainTableRow_7");

}  // namespace wh::databasemodule
