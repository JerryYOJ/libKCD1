#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "opp_actor_class"  row_size: 356
// Registration: 0x1800c3250
#pragma pack(push, 1)
struct S_OppActorClassTableRow_5 {
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
    float block_time_to_start;  // 0x098
    float block_time_to_hit;  // 0x09C
    float block_time_to_end;  // 0x0A0
    int32_t blocking_hand;  // 0x0A4
    float attack_time_to_spb_start;  // 0x0A8
    float attack_time_to_start;  // 0x0AC
    float attack_time_to_hit;  // 0x0B0
    float attack_time_to_withdraw;  // 0x0B4
    float attack_time_to_end;  // 0x0B8
    int32_t anim_hit_count;  // 0x0BC
    float perfect_block_window;  // 0x0C0
    float sync_riposte_window;  // 0x0C4
    float dodge_window;  // 0x0C8
    float hit_distance;  // 0x0CC
    int32_t attacking_hand;  // 0x0D0
    int32_t block_zone_id;  // 0x0D4
    int32_t opp_attack_type_id;  // 0x0D8
    int32_t input_class_id;  // 0x0DC
    int32_t attack_type_id;  // 0x0E0
    int32_t attack_zone_id;  // 0x0E4
    int32_t riposte_zone_id;  // 0x0E8
    int32_t r_weapon_class_id;  // 0x0EC
    int32_t l_weapon_class_id;  // 0x0F0
    int32_t r_weapon_group_id;  // 0x0F4
    int32_t l_weapon_group_id;  // 0x0F8
    int32_t opp_r_weapon_class_id;  // 0x0FC
    int32_t opp_l_weapon_class_id;  // 0x100
    int32_t opp_r_weapon_group_id;  // 0x104
    int32_t opp_l_weapon_group_id;  // 0x108
    int32_t guard_type_id;  // 0x10C
    int32_t guard_stance_id;  // 0x110
    int32_t opp_guard_stance_id;  // 0x114
    int32_t guard_zone_id;  // 0x118
    int32_t action_type_id;  // 0x11C
    int32_t end_guard_type_id;  // 0x120
    int32_t end_guard_zone_id;  // 0x124
    int32_t end_guard_stance_id;  // 0x128
    uint8_t _pad_0x12C[4];
    const char* blk_mn_fragment_id;  // 0x130
    uint8_t _pad_0x138[8];
    const char* blk_mn_tags;  // 0x140
    const char* z_spatial_grid;  // 0x148
    bool sync_hit_start_by_pc;  // 0x150
    bool has_hit_animevents;  // 0x151
    uint8_t _pad_0x152[14];
    float sync_point;  // 0x160
    // --- virtual columns (offset=-1, not in struct memory) ---
    // int32_t actor_class_hash;
};
#pragma pack(pop)
static_assert(sizeof(S_OppActorClassTableRow_5) == 356, "Size mismatch for S_OppActorClassTableRow_5");

}  // namespace wh::databasemodule
