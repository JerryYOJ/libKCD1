#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "soul_archetype"  row_size: 52
// Registration: 0x1801386d0
#pragma pack(push, 1)
struct S_SoulArchetypeTableRow {
    uint8_t _rowbase[4];  // 0x000
    int32_t soul_archetype_id;  // 0x004  // PK
    const char* soul_archetype_name;  // 0x008
    int32_t race_id;  // 0x010
    int32_t gender_id;  // 0x014
    float normal_body_weight;  // 0x018
    float body_base_armor;  // 0x01C
    float body_base_visibility;  // 0x020
    float body_base_conspicuousness;  // 0x024
    float inventory_capacity_multiplier;  // 0x028
    float base_stamina;  // 0x02C
    float relative_vitality_to_stamina;  // 0x030
};
#pragma pack(pop)
static_assert(sizeof(S_SoulArchetypeTableRow) == 52, "Size mismatch for S_SoulArchetypeTableRow");

}  // namespace wh::databasemodule
