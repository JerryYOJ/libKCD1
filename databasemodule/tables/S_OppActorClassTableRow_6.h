#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "opp_actor_class"  row_size: 264
// Registration: 0x1800c6960
#pragma pack(push, 1)
struct S_OppActorClassTableRow_6 {
    uint8_t _rowbase[4];  // 0x000
    int32_t opp_actor_class_hash;  // 0x004
    const char* opp_actor_classes;  // 0x008
    bool mounted;  // 0x010
    bool opp_mounted;  // 0x011
    uint8_t _pad_0x012[14];
    float animation_duration;  // 0x020
    float fade_in;  // 0x024
    uint8_t init_align0[28];  // 0x028
    uint8_t init_align1[28];  // 0x044
    uint8_t init_sec_align0[28];  // 0x060
    uint8_t init_sec_align1[28];  // 0x07C
    int32_t attacking_hand;  // 0x098
    int32_t attack_type_id;  // 0x09C
    int32_t input_class_id;  // 0x0A0
    int32_t attack_zone_id;  // 0x0A4
    int32_t block_zone_id;  // 0x0A8
    int32_t r_weapon_class_id;  // 0x0AC
    int32_t l_weapon_class_id;  // 0x0B0
    int32_t r_weapon_group_id;  // 0x0B4
    int32_t l_weapon_group_id;  // 0x0B8
    int32_t opp_r_weapon_class_id;  // 0x0BC
    int32_t opp_l_weapon_class_id;  // 0x0C0
    int32_t opp_r_weapon_group_id;  // 0x0C4
    int32_t opp_l_weapon_group_id;  // 0x0C8
    int32_t guard_type_id;  // 0x0CC
    int32_t guard_stance_id;  // 0x0D0
    int32_t opp_guard_stance_id;  // 0x0D4
    int32_t guard_zone_id;  // 0x0D8
    int32_t action_type_id;  // 0x0DC
    int32_t end_guard_type_id;  // 0x0E0
    int32_t end_guard_zone_id;  // 0x0E4
    int32_t end_guard_stance_id;  // 0x0E8
    uint8_t _pad_0x0EC[4];
    const char* mn_fragment_id;  // 0x0F0
    uint8_t _pad_0x0F8[8];
    const char* mn_tags;  // 0x100
    // --- virtual columns (offset=-1, not in struct memory) ---
    // int32_t actor_class_hash;
};
#pragma pack(pop)
static_assert(sizeof(S_OppActorClassTableRow_6) == 264, "Size mismatch for S_OppActorClassTableRow_6");

}  // namespace wh::databasemodule
