#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "soul"  row_size: 504
// Registration: 0x180140610
#pragma pack(push, 1)
struct S_SoulTableRow_3 {
    uint8_t _rowbase[16];  // 0x000
    uint64_t soul_id;  // 0x010  // PK
    // CryGUID inventory_id;  // 0x010 (alias)
    uint8_t _pad_0x018[24];
    float initial_clothing_dirt;  // 0x030
    uint8_t _pad_0x034[72];
    float character_scale;  // 0x07C
    uint8_t _pad_0x080[4];
    float character_skin_hue;  // 0x084
    uint8_t _pad_0x088[4];
    int32_t character_skin_color;  // 0x08C
    uint8_t _pad_0x090[4];
    float character_head_hue;  // 0x094
    uint8_t _pad_0x098[4];
    int32_t character_head_color;  // 0x09C
    uint8_t _pad_0x0A0[4];
    float character_eyes_occlusion_strength;  // 0x0A4
    uint8_t _pad_0x0A8[4];
    float character_hair_hue;  // 0x0AC
    uint8_t _pad_0x0B0[4];
    int32_t character_hair_color;  // 0x0B4
    uint8_t _pad_0x0B8[4];
    float character_beard_hue;  // 0x0BC
    uint8_t _pad_0x0C0[4];
    int32_t character_beard_color;  // 0x0C4
    CryGUID initial_weapon_preset_id;  // 0x0C8
    const char* soul_name;  // 0x0D8
    int32_t soul_class_id;  // 0x0E0
    int32_t soul_vip_class_id;  // 0x0E4
    int32_t social_class_id;  // 0x0E8
    uint8_t _pad_0x0EC[4];
    int32_t soul_archetype_id;  // 0x0F0
    int32_t faction;  // 0x0F4
    float xp_multiplier;  // 0x0F8
    float digestion_multiplier;  // 0x0FC
    uint8_t _pad_0x100[4];
    float shadiness;  // 0x104
    int32_t charisma;  // 0x108
    int32_t str;  // 0x10C
    int32_t agi;  // 0x110
    int32_t vit;  // 0x114
    int32_t spc;  // 0x118
    int32_t vision;  // 0x11C
    int32_t hearing;  // 0x120
    int32_t barter;  // 0x124
    int32_t courage;  // 0x128
    float reputation;  // 0x12C
    CryGUID brain_id;  // 0x130
    CryGUID ai_body_id;  // 0x140
    const char* activity_0;  // 0x150
    const char* time_0;  // 0x158
    const char* activity_1;  // 0x160
    const char* time_1;  // 0x168
    const char* activity_2;  // 0x170
    const char* time_2;  // 0x178
    const char* activity_3;  // 0x180
    const char* time_3;  // 0x188
    const char* activity_4;  // 0x190
    const char* time_4;  // 0x198
    const char* activity_5;  // 0x1A0
    const char* time_5;  // 0x1A8
    const char* activity_6;  // 0x1B0
    const char* time_6;  // 0x1B8
    const char* activity_7;  // 0x1C0
    const char* time_7;  // 0x1C8
    const char* activity_8;  // 0x1D0
    const char* time_8;  // 0x1D8
    const char* computer_name;  // 0x1E0
    const char* timestamp;  // 0x1E8
    const char* level_name;  // 0x1F0
    // --- virtual columns (offset=-1, not in struct memory) ---
    // uint64_t character_body_id;
    // uint64_t character_head_id;
    // uint64_t character_hair_id;
    // uint64_t character_beard_id;
    // int32_t character_skin_brightness;
    // int32_t character_skin_saturation;
    // int32_t character_head_brightness;
    // int32_t character_head_saturation;
    // int32_t character_hair_brightness;
    // int32_t character_hair_saturation;
    // int32_t character_beard_brightness;
    // int32_t character_beard_saturation;
};
#pragma pack(pop)
static_assert(sizeof(S_SoulTableRow_3) == 504, "Size mismatch for S_SoulTableRow_3");

}  // namespace wh::databasemodule
