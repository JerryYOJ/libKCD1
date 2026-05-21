#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "subbrain"  row_size: 66
// Registration: 0x1801dff90
#pragma pack(push, 1)
struct S_SubbrainTableRow_6 {
    uint8_t _rowbase[16];  // 0x000
    uint64_t subbrain_id;  // 0x010  // PK
    // const char* file_name;  // 0x010 (alias)
    const char* on_request_tree;  // 0x018
    const char* on_release_tree;  // 0x020
    const char* on_update_tree;  // 0x028
    const char* on_enter_tree;  // 0x030
    const char* on_exit_tree;  // 0x038
    bool explicit_initialization;  // 0x040
    bool system_variables;  // 0x041
};
#pragma pack(pop)
static_assert(sizeof(S_SubbrainTableRow_6) == 66, "Size mismatch for S_SubbrainTableRow_6");

}  // namespace wh::databasemodule
