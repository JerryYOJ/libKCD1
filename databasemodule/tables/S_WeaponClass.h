#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "weapon_class"  row_size: 144
// Registration: 0x1800ff4a0
#pragma pack(push, 1)
struct S_WeaponClass {
    uint8_t _rowbase[4];  // 0x000
    int32_t weapon_class_id;  // 0x004  // PK
    const char* weapon_class_name;  // 0x008
    int32_t skill_id;  // 0x010
    int32_t attachment_slot_id;  // 0x014
    int32_t weapon_equip_slot_id;  // 0x018
    bool in_right_hand;  // 0x01C
    uint8_t _pad_0x01D[3];
    int32_t holster_slot_id;  // 0x020
    int32_t primary_attack_type_id;  // 0x024
    int32_t secondary_attack_type_id;  // 0x028
    float attack_distance;  // 0x02C
    bool is_blocking;  // 0x030
    uint8_t _pad_0x031[3];
    float sync_guard_distance;  // 0x034
    int32_t sync_guard_priority;  // 0x038
    int32_t item_manipulation_type;  // 0x03C
    float max_attack_distance;  // 0x040
    int32_t collision_mode;  // 0x044
    int32_t anim_collision_mode;  // 0x048
    int32_t combat_priority;  // 0x04C
    bool is_twohanded;  // 0x050
    uint8_t _pad_0x051[3];
    float horse_pull_down_distance;  // 0x054
    float horse_pull_down_max_speed;  // 0x058
    float horse_pull_down_z_tolerance;  // 0x05C
    float hunt_attack_distance;  // 0x060
    float zone_change_timeout_coef;  // 0x064
    uint8_t _pad_0x068[32];
    int32_t sharpening_zone_count;  // 0x088
    int32_t gender_id;  // 0x08C
    // --- virtual columns (offset=-1, not in struct memory) ---
    // uint64_t draw_buff_id;
    // uint64_t alternative_draw_buff_id;
};
#pragma pack(pop)
static_assert(sizeof(S_WeaponClass) == 144, "Size mismatch for S_WeaponClass");

}  // namespace wh::databasemodule
