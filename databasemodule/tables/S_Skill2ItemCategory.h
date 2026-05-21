#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "skill"  row_size: 16
// Registration: 0x180120b50
#pragma pack(push, 1)
struct S_Skill2ItemCategory {
    uint8_t _rowbase[4];  // 0x000
    int32_t skill_id;  // 0x004  // PK
    const char* item_category;  // 0x008  // PK
};
#pragma pack(pop)
static_assert(sizeof(S_Skill2ItemCategory) == 16, "Size mismatch for S_Skill2ItemCategory");

}  // namespace wh::databasemodule
