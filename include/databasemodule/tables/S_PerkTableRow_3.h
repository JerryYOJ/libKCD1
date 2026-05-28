#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "perk"  row_size: 40
// Registration: 0x18011cb30
#pragma pack(push, 1)
struct S_PerkTableRow_3 {
    uint8_t _rowbase[16];  // 0x000
    uint64_t perk_id;  // 0x010  // PK
    // int32_t codex_ui_page_id;  // 0x010 (alias)
    // int32_t codex_ui_layout_id;  // 0x014 (alias)
    const char* codex_ui_text;  // 0x018
    const char* codex_ui_image;  // 0x020
};
#pragma pack(pop)
static_assert(sizeof(S_PerkTableRow_3) == 40, "Size mismatch for S_PerkTableRow_3");

}  // namespace wh::databasemodule
