#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "mn_option_index"  row_size: 65
// Registration: 0x1800efb80
#pragma pack(push, 1)
struct S_MnOptionIndexTableRow_5 {
    uint8_t _rowbase[4];  // 0x000
    int32_t mn_option_index;  // 0x004  // PK
    const char* mn_fragment_id;  // 0x008  // PK
    // const char* mn_tags;  // 0x008 (alias)  // PK
    uint8_t _pad_0x010[4];
    int32_t mn_move_speed_tag;  // 0x014
    int32_t mn_stance_tag;  // 0x018
    float jump_height;  // 0x01C
    float jump_total_time;  // 0x020
    float jump_peak_time;  // 0x024
    float jump_speed;  // 0x028
    float jump_length;  // 0x02C
    int32_t actor_class_hash;  // 0x030
    uint8_t _pad_0x034[12];
    bool proc_clip_present;  // 0x040
};
#pragma pack(pop)
static_assert(sizeof(S_MnOptionIndexTableRow_5) == 65, "Size mismatch for S_MnOptionIndexTableRow_5");

}  // namespace wh::databasemodule
