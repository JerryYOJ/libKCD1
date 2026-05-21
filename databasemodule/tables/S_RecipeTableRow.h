#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "recipe"  row_size: 68
// Registration: 0x18014c210
#pragma pack(push, 1)
struct S_RecipeTableRow {
    uint8_t _rowbase[4];  // 0x000
    int32_t recipe_id;  // 0x004  // PK
    CryGUID product_item_id;  // 0x008
    CryGUID base_material_id;  // 0x018
    const char* ui_name;  // 0x028
    const char* ui_usage;  // 0x030
    const char* ui_stats;  // 0x038
    int32_t max_yield;  // 0x040
};
#pragma pack(pop)
static_assert(sizeof(S_RecipeTableRow) == 68, "Size mismatch for S_RecipeTableRow");

}  // namespace wh::databasemodule
