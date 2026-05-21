#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "mn_frag_tag"  row_size: 66
// Registration: 0x1800f0f80
#pragma pack(push, 1)
struct S_MnFragTagTableRow {
    uint8_t _rowbase[8];  // 0x000
    const char* mn_frag_tag_state;  // 0x008
    int32_t mn_option_idx;  // 0x010
    int16_t hand_offset;  // 0x014
    int16_t hand_rot;  // 0x020
    float hand_rot_w;  // 0x02C
    int32_t actor_class_hash;  // 0x030
    bool is_right_hand;  // 0x034
    uint8_t _pad_0x035[11];
    bool IsBSpace;  // 0x040
    bool IsSpecialized;  // 0x041
    // --- virtual columns (offset=-1, not in struct memory) ---
    // const char* mn_fragment;
};
#pragma pack(pop)
static_assert(sizeof(S_MnFragTagTableRow) == 66, "Size mismatch for S_MnFragTagTableRow");

}  // namespace wh::databasemodule
