#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "sequence_line"  row_size: 24
// Registration: 0x1800e6bc0
#pragma pack(push, 1)
struct S_SequenceLineTableRow_8 {
    uint8_t _rowbase[4];  // 0x000
    int32_t sequence_line_id;  // 0x004  // PK
    // int32_t voice_id;  // 0x004 (alias)  // PK
    const char* wave_file;  // 0x008
    uint8_t _pad_0x010[4];
    int32_t path;  // 0x014
};
#pragma pack(pop)
static_assert(sizeof(S_SequenceLineTableRow_8) == 24, "Size mismatch for S_SequenceLineTableRow_8");

}  // namespace wh::databasemodule
