#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "perk"  row_size: 24
// Registration: 0x18011e810
#pragma pack(push, 1)
struct S_PerkTableRow_8 {
    uint8_t _rowbase[16];  // 0x000
    uint64_t perk_id;  // 0x010  // PK
    // const char* perk_editor_name;  // 0x010 (alias)
};
#pragma pack(pop)
static_assert(sizeof(S_PerkTableRow_8) == 24, "Size mismatch for S_PerkTableRow_8");

}  // namespace wh::databasemodule
