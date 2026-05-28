#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "structure_addon_group"  row_size: 8
// Registration: 0x180147f50
#pragma pack(push, 1)
struct S_NewHomesStructureAddonGroup {
    uint8_t _rowbase[4];  // 0x000
    int32_t structure_addon_group_id;  // 0x004  // PK
};
#pragma pack(pop)
static_assert(sizeof(S_NewHomesStructureAddonGroup) == 8, "Size mismatch for S_NewHomesStructureAddonGroup");

}  // namespace wh::databasemodule
