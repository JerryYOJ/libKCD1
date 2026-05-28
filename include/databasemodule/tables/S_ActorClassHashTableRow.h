#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "actor_class_hash"  row_size: 48
// Registration: 0x1800dbc50
#pragma pack(push, 1)
struct S_ActorClassHashTableRow {
    uint8_t _rowbase[4];  // 0x000
    int32_t actor_class_hash;  // 0x004  // PK
    // int32_t mn_option_index;  // 0x004 (alias)  // PK
    const char* mn_fragment_id;  // 0x008  // PK
    // const char* mn_tags;  // 0x008 (alias)  // PK
    uint8_t _pad_0x010[24];
    float start_time;  // 0x028
    float end_time;  // 0x02C
};
#pragma pack(pop)
static_assert(sizeof(S_ActorClassHashTableRow) == 48, "Size mismatch for S_ActorClassHashTableRow");

}  // namespace wh::databasemodule
