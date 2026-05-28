#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "actor_class_hash"  row_size: 56
// Registration: 0x1800dc300
#pragma pack(push, 1)
struct S_ActorClassHashTableRow_2 {
    uint8_t _rowbase[4];  // 0x000
    int32_t actor_class_hash;  // 0x004  // PK
    // int32_t mn_option_index;  // 0x004 (alias)  // PK
    const char* mn_fragment_id;  // 0x008  // PK
    // const char* mn_tags;  // 0x008 (alias)  // PK
    uint8_t _pad_0x010[24];
    const char* event_name;  // 0x028
    float abs_event_time;  // 0x030
    float norm_event_time;  // 0x034
};
#pragma pack(pop)
static_assert(sizeof(S_ActorClassHashTableRow_2) == 56, "Size mismatch for S_ActorClassHashTableRow_2");

}  // namespace wh::databasemodule
