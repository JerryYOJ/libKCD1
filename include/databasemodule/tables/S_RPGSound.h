#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "rpg_sound"  row_size: 40
// Registration: 0x18011f0d0
#pragma pack(push, 1)
struct S_RPGSound {
    uint8_t _rowbase[4];  // 0x000
    int32_t rpg_sound_id;  // 0x004  // PK
    const char* rpg_sound_name;  // 0x008
    float intensity_per_second;  // 0x010
    float intensity_oneshot;  // 0x014
    float decrement_per_second;  // 0x018
    float notification_cooldown;  // 0x01C
    float notification_threshold;  // 0x020
    float noisiness_multiplier;  // 0x024
};
#pragma pack(pop)
static_assert(sizeof(S_RPGSound) == 40, "Size mismatch for S_RPGSound");

}  // namespace wh::databasemodule
