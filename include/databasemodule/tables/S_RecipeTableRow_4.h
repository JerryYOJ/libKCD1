#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "recipe"  row_size: 16
// Registration: 0x18014d080
#pragma pack(push, 1)
struct S_RecipeTableRow_4 {
    uint8_t _rowbase[4];  // 0x000
    int32_t recipe_id;  // 0x004  // PK
    // int32_t recipe_step_id;  // 0x004 (alias)  // PK
    // int32_t recipe_substep_id;  // 0x004 (alias)  // PK
    uint8_t _pad_0x008[4];
    int32_t recipe_substep_type_id;  // 0x00C
};
#pragma pack(pop)
static_assert(sizeof(S_RecipeTableRow_4) == 16, "Size mismatch for S_RecipeTableRow_4");

}  // namespace wh::databasemodule
