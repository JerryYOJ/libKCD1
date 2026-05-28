#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "opp_actor_class"  row_size: 344
// Registration: 0x1800b1080
#pragma pack(push, 1)
struct S_OppActorClassTableRow {
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
    float attack_time_to_spb_start;  // 0x098
    float attack_time_to_start;  // 0x09C
    float attack_time_to_hit;  // 0x0A0
    float attack_time_to_withdraw;  // 0x0A4
    float attack_time_to_end;  // 0x0A8
    int32_t anim_hit_count;  // 0x0AC
    float perfect_block_window;  // 0x0B0
    float sync_riposte_window;  // 0x0B4
    float dodge_window;  // 0x0B8
    float hit_distance;  // 0x0BC
    int32_t attacking_hand;  // 0x0C0
    int32_t attack_zone_id;  // 0x0C4
    int32_t attack_type_id;  // 0x0C8
    int32_t input_class_id;  // 0x0CC
    int32_t actor_pose_id;  // 0x0D0
    int32_t opp_actor_pose_id;  // 0x0D4
    int32_t r_weapon_class_id;  // 0x0D8
    int32_t l_weapon_class_id;  // 0x0DC
    int32_t r_weapon_group_id;  // 0x0E0
    int32_t l_weapon_group_id;  // 0x0E4
    int32_t opp_r_weapon_class_id;  // 0x0E8
    int32_t opp_l_weapon_class_id;  // 0x0EC
    int32_t opp_r_weapon_group_id;  // 0x0F0
    int32_t opp_l_weapon_group_id;  // 0x0F4
    int32_t guard_type_id;  // 0x0F8
    int32_t guard_stance_id;  // 0x0FC
    int32_t opp_guard_stance_id;  // 0x100
    int32_t guard_zone_id;  // 0x104
    int32_t action_type_id;  // 0x108
    int32_t end_guard_type_id;  // 0x10C
    int32_t end_guard_zone_id;  // 0x110
    int32_t end_guard_stance_id;  // 0x114
    bool virtual_dagger;  // 0x118
    uint8_t _pad_0x119[7];
    const char* mn_fragment_id;  // 0x120
    uint8_t _pad_0x128[8];
    const char* mn_tags;  // 0x130
    float min_optimal_distance;  // 0x138
    float max_optimal_distance;  // 0x13C
    float min_block_distance;  // 0x140
    float max_block_distance;  // 0x144
    float block_distance;  // 0x148
    bool player;  // 0x14C
    bool has_hit_animevents;  // 0x14D
    uint8_t _pad_0x14E[2];
    const char* z_spatial_grid;  // 0x150
    // --- virtual columns (offset=-1, not in struct memory) ---
    // int32_t actor_class_hash;
};
#pragma pack(pop)
static_assert(sizeof(S_OppActorClassTableRow) == 344, "Size mismatch for S_OppActorClassTableRow");

}  // namespace wh::databasemodule
