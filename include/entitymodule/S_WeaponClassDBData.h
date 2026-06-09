#pragma once

#include <cstdint>

// ===========================================================================
// S_WeaponClassDBData — runtime weapon-class row.
//
// Value type of C_ObjectDatabaseIdIndexed<C_ObjectTableDatabase<S_WeaponClass,
// S_WeaponClassDBData>, int> (a.k.a. C_WeaponClassDatabase, table "weapon_class").
// The combat action loaders resolve r/l/opp weapon_class_id columns into a
// pointer to this row (resolver sub_180F7430C; default/sentinel sub_180724404).
//
// Layout mirrors the already-RE'd S_WeaponClass table row (databasemodule) for
// the +0x08..+0x64 region — confirmed by the sentinel builder, which sets
// weapon_class_name@+0x08, combat_priority@+0x4C, the three horse_pull_down
// floats@+0x54..+0x5C (to -1.0), and two runtime Vec4s @+0x68/+0x78.
//
// VERIFIED (sentinel sub_180724404): id@+0x00, name@+0x08, the -1.0 distance
// floats, the +0x68/+0x78 vectors. Fields +0x10..+0x64 are named from the
// S_WeaponClass row schema (offsets match). _field04 and the exact contents of
// the two trailing Vec4s are UNVERIFIED.
// ===========================================================================

namespace wh::entitymodule {

struct S_WeaponClassDBData {
    int32_t     weapon_class_id;            // +0x00
    int32_t     _field04;                   // +0x04  [UNVERIFIED]
    const char* weapon_class_name;          // +0x08  CryStringT<char>
    int32_t     skill_id;                   // +0x10
    int32_t     attachment_slot_id;         // +0x14
    int32_t     weapon_equip_slot_id;       // +0x18
    bool        in_right_hand;              // +0x1C
    uint8_t     _pad1D[3];                  // +0x1D
    int32_t     holster_slot_id;            // +0x20
    int32_t     primary_attack_type_id;     // +0x24
    int32_t     secondary_attack_type_id;   // +0x28
    float       attack_distance;            // +0x2C
    bool        is_blocking;                // +0x30
    uint8_t     _pad31[3];                  // +0x31
    float       sync_guard_distance;        // +0x34
    int32_t     sync_guard_priority;        // +0x38
    int32_t     item_manipulation_type;     // +0x3C
    float       max_attack_distance;        // +0x40
    int32_t     collision_mode;             // +0x44
    int32_t     anim_collision_mode;        // +0x48
    int32_t     combat_priority;            // +0x4C
    bool        is_twohanded;               // +0x50
    uint8_t     _pad51[3];                  // +0x51
    float       horse_pull_down_distance;   // +0x54
    float       horse_pull_down_max_speed;  // +0x58
    float       horse_pull_down_z_tolerance; // +0x5C
    float       hunt_attack_distance;       // +0x60
    float       zone_change_timeout_coef;   // +0x64
    float       _runtimeVec68[4];           // +0x68  runtime Vec4 [UNVERIFIED contents]
    float       _runtimeVec78[4];           // +0x78  runtime Vec4 [UNVERIFIED contents]
};
static_assert(sizeof(S_WeaponClassDBData) == 0x88);

}  // namespace wh::entitymodule
