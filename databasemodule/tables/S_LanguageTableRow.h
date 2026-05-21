#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "language"  row_size: 12
// Registration: 0x180111360
#pragma pack(push, 1)
struct S_LanguageTableRow {
    uint8_t _rowbase[4];  // 0x000
    int32_t language_id;  // 0x004  // PK
    // int32_t audio_track_id;  // 0x004 (alias)
    int32_t subtitles_track_id;  // 0x008
};
#pragma pack(pop)
static_assert(sizeof(S_LanguageTableRow) == 12, "Size mismatch for S_LanguageTableRow");

}  // namespace wh::databasemodule
