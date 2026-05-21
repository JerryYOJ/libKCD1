#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "sequence_line"  row_size: 32
// Registration: 0x1800e1220
#pragma pack(push, 1)
struct S_SequenceLineTableRow {
    uint8_t _rowbase[4];  // 0x000
    int32_t sequence_line_id;  // 0x004  // PK
    // int32_t dialogue_command_type;  // 0x004 (alias)
    uint8_t _pad_0x008[8];
    const char* char_param;  // 0x010
    int32_t who;  // 0x018
    int32_t target;  // 0x01C
};
#pragma pack(pop)
static_assert(sizeof(S_SequenceLineTableRow) == 32, "Size mismatch for S_SequenceLineTableRow");

}  // namespace wh::databasemodule
