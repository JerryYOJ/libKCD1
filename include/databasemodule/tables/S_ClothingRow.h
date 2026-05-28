#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "clothing"  row_size: 96
// Registration: 0x1800f2960
#pragma pack(push, 1)
struct S_ClothingRow {
    uint8_t _rowbase[8];  // 0x000
    const char* timestamp;  // 0x008
    uint64_t clothing_id;  // 0x010  // PK
    uint8_t _pad_0x018[8];
    const char* clothing_name;  // 0x020
    int32_t race_id;  // 0x028
    int32_t gender_id;  // 0x02C
    const char* model;  // 0x030
    const char* material;  // 0x038
    float lod_persistence;  // 0x040
    uint8_t _pad_0x044[4];
    int32_t influence_type;  // 0x048
    int32_t armor_archetype_id;  // 0x04C
    int32_t intersection_translucency_min;  // 0x050
    int32_t intersection_translucency_max;  // 0x054
    const char* morph_target;  // 0x058
    // --- virtual columns (offset=-1, not in struct memory) ---
    // const char* computer_name;
};
#pragma pack(pop)
static_assert(sizeof(S_ClothingRow) == 96, "Size mismatch for S_ClothingRow");

}  // namespace wh::databasemodule
