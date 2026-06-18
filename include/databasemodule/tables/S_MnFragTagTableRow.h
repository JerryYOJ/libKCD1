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
    int16_t hand_offset;  // 0x014  (under-typed: occupies a 12-byte slot, likely a Vec3 — see _pad below)
    uint8_t _pad_0x016[10];  // 0x016..0x020  trailing bytes of the hand_offset column (unmapped by auto-RE)
    int16_t hand_rot;  // 0x020  (under-typed: occupies a 12-byte slot, likely a Vec3)
    uint8_t _pad_0x022[10];  // 0x022..0x02C  trailing bytes of the hand_rot column
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
