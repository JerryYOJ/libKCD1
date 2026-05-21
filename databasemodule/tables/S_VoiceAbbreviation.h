#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "abbreviation"  row_size: 16
// Registration: 0x1800e57f0
#pragma pack(push, 1)
struct S_VoiceAbbreviation {
    uint8_t _rowbase[8];  // 0x000
    const char* abbreviation;  // 0x008
    // --- virtual columns (offset=-1, not in struct memory) ---
    // int32_t voice_id;
};
#pragma pack(pop)
static_assert(sizeof(S_VoiceAbbreviation) == 16, "Size mismatch for S_VoiceAbbreviation");

}  // namespace wh::databasemodule
