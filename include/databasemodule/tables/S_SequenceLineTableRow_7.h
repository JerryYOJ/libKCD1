#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "sequence_line"  row_size: 28
// Registration: 0x1800e66a0
#pragma pack(push, 1)
struct S_SequenceLineTableRow_7 {
    uint8_t _rowbase[4];  // 0x000
    int32_t sequence_line_id;  // 0x004  // PK
    const char* string_name;  // 0x008
    int32_t role_id;  // 0x010
    int32_t camera_mode;  // 0x014
    int32_t response_volume_id;  // 0x018
};
#pragma pack(pop)
static_assert(sizeof(S_SequenceLineTableRow_7) == 28, "Size mismatch for S_SequenceLineTableRow_7");

}  // namespace wh::databasemodule
