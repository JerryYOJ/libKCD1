#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "mn_fragment_id"  row_size: 76
// Registration: 0x1800def10
#pragma pack(push, 1)
struct S_MnFragmentIdTableRow {
    uint8_t _rowbase[8];  // 0x000
    const char* mn_fragment_id_str;  // 0x008
    const char* mn_tag_state_str;  // 0x010
    int32_t mn_option_index;  // 0x018
    uint8_t _pad_0x01C[12];
    bool is_fullbody;  // 0x028
    uint8_t _pad_0x029[3];
    int32_t hit_reaction_type_id;  // 0x02C
    int32_t speed_tag;  // 0x030
    int32_t stance_tag;  // 0x034
    bool is_mounted;  // 0x038
    bool is_carryCorpse;  // 0x039
    bool is_player;  // 0x03A
    uint8_t _pad_0x03B[1];
    int32_t r_attacker_man_type;  // 0x03C
    int32_t l_attacker_man_type;  // 0x040
    int32_t r_target_man_type;  // 0x044
    int32_t l_target_man_type;  // 0x048
    // --- virtual columns (offset=-1, not in struct memory) ---
    // int32_t actor_class_hash;
};
#pragma pack(pop)
static_assert(sizeof(S_MnFragmentIdTableRow) == 76, "Size mismatch for S_MnFragmentIdTableRow");

}  // namespace wh::databasemodule
