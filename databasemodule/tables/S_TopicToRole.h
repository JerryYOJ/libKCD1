#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "topic"  row_size: 8
// Registration: 0x1800e52f0
#pragma pack(push, 1)
struct S_TopicToRole {
    uint8_t _rowbase[4];  // 0x000
    int32_t topic_id;  // 0x004  // PK
    // int32_t role_id;  // 0x004 (alias)  // PK
};
#pragma pack(pop)
static_assert(sizeof(S_TopicToRole) == 8, "Size mismatch for S_TopicToRole");

}  // namespace wh::databasemodule
