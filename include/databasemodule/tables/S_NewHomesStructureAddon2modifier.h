#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "structure_addon"  row_size: 8
// Registration: 0x180147180
#pragma pack(push, 1)
struct S_NewHomesStructureAddon2modifier {
    uint8_t _rowbase[4];  // 0x000
    int32_t structure_addon_id;  // 0x004  // PK
    // int32_t modifier_id;  // 0x004 (alias)  // PK
};
#pragma pack(pop)
static_assert(sizeof(S_NewHomesStructureAddon2modifier) == 8, "Size mismatch for S_NewHomesStructureAddon2modifier");

}  // namespace wh::databasemodule
