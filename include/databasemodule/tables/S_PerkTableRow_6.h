#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "perk"  row_size: 104
// Registration: 0x18011d720
#pragma pack(push, 1)
struct S_PerkTableRow_6 {
    uint8_t _rowbase[16];  // 0x000
    uint64_t perk_id;  // 0x010  // PK
    uint8_t _pad_0x018[8];
    const char* perk_name;  // 0x020
    const char* perk_ui_name;  // 0x028
    const char* perk_ui_desc;  // 0x030
    const char* icon_id;  // 0x038
    int32_t stat_selector;  // 0x040
    int32_t skill_selector;  // 0x044
    int32_t level;  // 0x048
    int32_t visibility;  // 0x04C
    uint8_t _pad_0x050[16];
    int32_t ui_priority;  // 0x060
    int32_t exclude_in_game_mode;  // 0x064
    // --- virtual columns (offset=-1, not in struct memory) ---
    // uint64_t parent_id;
    // uint64_t metaperk_id;
};
#pragma pack(pop)
static_assert(sizeof(S_PerkTableRow_6) == 104, "Size mismatch for S_PerkTableRow_6");

}  // namespace wh::databasemodule
