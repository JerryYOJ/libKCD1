#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "mn_option_index"  row_size: 192
// Registration: 0x1800c2160
#pragma pack(push, 1)
struct S_MnOptionIndexTableRow_3 {
    uint8_t _rowbase[4];  // 0x000
    int32_t opp_actor_class_hash;  // 0x004
    // int32_t mn_option_index;  // 0x004 (alias)  // PK
    const char* opp_actor_classes;  // 0x008
    // const char* mn_fragment_id;  // 0x008 (alias)  // PK
    // const char* mn_tags;  // 0x008 (alias)  // PK
    bool mounted;  // 0x010
    bool opp_mounted;  // 0x011
    uint8_t _pad_0x012[14];
    float animation_duration;  // 0x020
    float fade_in;  // 0x024
    uint8_t init_align0[28];  // 0x028
    uint8_t init_align1[28];  // 0x044
    uint8_t init_sec_align0[28];  // 0x060
    uint8_t init_sec_align1[28];  // 0x07C
    uint8_t _pad_0x098[24];
    float min_distance;  // 0x0B0
    float max_distance;  // 0x0B4
    bool player;  // 0x0B8
    uint8_t _pad_0x0B9[3];
    int32_t guard_stance_id;  // 0x0BC
    // --- virtual columns (offset=-1, not in struct memory) ---
    // int32_t actor_class_hash;
};
#pragma pack(pop)
static_assert(sizeof(S_MnOptionIndexTableRow_3) == 192, "Size mismatch for S_MnOptionIndexTableRow_3");

}  // namespace wh::databasemodule
