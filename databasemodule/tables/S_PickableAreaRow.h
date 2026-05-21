#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "id"  row_size: 64
// Registration: 0x18010d760
#pragma pack(push, 1)
struct S_PickableAreaRow {
    uint8_t _rowbase[4];  // 0x000
    int32_t id;  // 0x004  // PK
    const char* name;  // 0x008
    int32_t amount;  // 0x010
    float respawn_time;  // 0x014
    uint8_t _pad_0x018[16];
    float anim_speed;  // 0x028
    uint8_t _pad_0x02C[4];
    const char* anim_fragment;  // 0x030
    const char* anim_tags;  // 0x038
};
#pragma pack(pop)
static_assert(sizeof(S_PickableAreaRow) == 64, "Size mismatch for S_PickableAreaRow");

}  // namespace wh::databasemodule
