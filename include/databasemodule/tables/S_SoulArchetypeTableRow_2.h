#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "soul_archetype"  row_size: 40
// Registration: 0x180139280
#pragma pack(push, 1)
struct S_SoulArchetypeTableRow_2 {
    uint8_t _rowbase[4];  // 0x000
    int32_t soul_archetype_id;  // 0x004  // PK
    // int32_t stance_id;  // 0x004 (alias)  // PK
    // int32_t logical_speed;  // 0x004 (alias)  // PK
    uint8_t _pad_0x008[4];
    int32_t rpg_movement_type_id;  // 0x00C
    float real_speed_min;  // 0x010
    float real_speed_max;  // 0x014
    float real_backward_speed_min;  // 0x018
    float real_backward_speed_max;  // 0x01C
    const char* mn_tag;  // 0x020
};
#pragma pack(pop)
static_assert(sizeof(S_SoulArchetypeTableRow_2) == 40, "Size mismatch for S_SoulArchetypeTableRow_2");

}  // namespace wh::databasemodule
