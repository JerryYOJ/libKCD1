#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "recipe"  row_size: 24
// Registration: 0x18014cc50
#pragma pack(push, 1)
struct S_RecipeTableRow_3 {
    uint8_t _rowbase[4];  // 0x000
    int32_t recipe_id;  // 0x004  // PK
    // int32_t recipe_step_id;  // 0x004 (alias)  // PK
    const char* ui_text;  // 0x008
    const char* condition;  // 0x010
};
#pragma pack(pop)
static_assert(sizeof(S_RecipeTableRow_3) == 24, "Size mismatch for S_RecipeTableRow_3");

}  // namespace wh::databasemodule
