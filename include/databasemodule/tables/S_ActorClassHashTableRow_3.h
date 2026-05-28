#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "actor_class_hash"  row_size: 136
// Registration: 0x1800dcaa0
#pragma pack(push, 1)
struct S_ActorClassHashTableRow_3 {
    uint8_t _rowbase[4];  // 0x000
    int32_t actor_class_hash;  // 0x004  // PK
    // int32_t mn_option_index;  // 0x004 (alias)  // PK
    const char* mn_fragment_id;  // 0x008  // PK
    // const char* mn_tags;  // 0x008 (alias)  // PK
    uint8_t _pad_0x010[24];
    bool looped;  // 0x028
    bool aligned;  // 0x029
    uint8_t _pad_0x02A[2];
    int16_t align_tm_pos;  // 0x02C
    int16_t align_tm_rotv;  // 0x038
    float align_tm_rotw;  // 0x044
    uint8_t align_secondary[28];  // 0x048
    float relative_movement_y;  // 0x064
    float total_duration;  // 0x068
    uint8_t relative_movement[28];  // 0x06C
};
#pragma pack(pop)
static_assert(sizeof(S_ActorClassHashTableRow_3) == 136, "Size mismatch for S_ActorClassHashTableRow_3");

}  // namespace wh::databasemodule
