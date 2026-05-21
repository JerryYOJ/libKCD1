#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "skald_subchapter"  row_size: 16
// Registration: 0x18014ff70
#pragma pack(push, 1)
struct S_SkaldQuestString {
    uint8_t _rowbase[4];  // 0x000
    int32_t skald_subchapter_id;  // 0x004  // PK
    // int32_t skald_quest_string_type_id;  // 0x004 (alias)  // PK
    const char* string_name;  // 0x008
};
#pragma pack(pop)
static_assert(sizeof(S_SkaldQuestString) == 16, "Size mismatch for S_SkaldQuestString");

}  // namespace wh::databasemodule
