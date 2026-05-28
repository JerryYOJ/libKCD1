#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "recipe"  row_size: 28
// Registration: 0x18014c910
#pragma pack(push, 1)
struct S_RecipeTableRow_2 {
    uint8_t _rowbase[4];  // 0x000
    int32_t recipe_id;  // 0x004  // PK
    uint8_t _pad_0x008[8];
    uint64_t item_id;  // 0x010  // PK
    int32_t quantity;  // 0x018
};
#pragma pack(pop)
static_assert(sizeof(S_RecipeTableRow_2) == 28, "Size mismatch for S_RecipeTableRow_2");

}  // namespace wh::databasemodule
