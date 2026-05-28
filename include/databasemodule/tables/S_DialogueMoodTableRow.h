#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "dialogue_mood"  row_size: 24
// Registration: 0x1800e2290
#pragma pack(push, 1)
struct S_DialogueMoodTableRow {
    uint8_t _rowbase[4];  // 0x000
    int32_t dialogue_mood_id;  // 0x004  // PK
    const char* dialogue_mood_name;  // 0x008
    const char* tag_name;  // 0x010
};
#pragma pack(pop)
static_assert(sizeof(S_DialogueMoodTableRow) == 24, "Size mismatch for S_DialogueMoodTableRow");

}  // namespace wh::databasemodule
