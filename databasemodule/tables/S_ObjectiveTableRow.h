#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "objective"  row_size: 64
// Registration: 0x180152d20
#pragma pack(push, 1)
struct S_ObjectiveTableRow {
    uint8_t _rowbase[4];  // 0x000
    int32_t objective_id;  // 0x004  // PK
    // int32_t quest_id;  // 0x004 (alias)  // PK
    const char* objective_name;  // 0x008
    uint8_t _pad_0x010[4];
    bool is_hidden;  // 0x014
    bool is_exclusive;  // 0x015
    uint8_t _pad_0x016[2];
    int32_t time;  // 0x018
    int32_t autocomplete_timeout;  // 0x01C
    const char* condition;  // 0x020
    uint8_t _pad_0x028[8];
    const char* expiration_timeout_str;  // 0x030
    const char* autocomplete_timeout_str;  // 0x038
};
#pragma pack(pop)
static_assert(sizeof(S_ObjectiveTableRow) == 64, "Size mismatch for S_ObjectiveTableRow");

}  // namespace wh::databasemodule
