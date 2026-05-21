#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "hit_reaction_type"  row_size: 29
// Registration: 0x1800dea00
#pragma pack(push, 1)
struct S_HitReactionTypeTableRow {
    uint8_t _rowbase[4];  // 0x000
    int32_t hit_reaction_type_id;  // 0x004  // PK
    const char* hit_reaction_type_name;  // 0x008
    const char* mn_tag;  // 0x010
    float physical_coef;  // 0x018
    bool is_death_reaction;  // 0x01C
};
#pragma pack(pop)
static_assert(sizeof(S_HitReactionTypeTableRow) == 29, "Size mismatch for S_HitReactionTypeTableRow");

}  // namespace wh::databasemodule
