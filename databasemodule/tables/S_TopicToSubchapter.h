#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "start_topic"  row_size: 8
// Registration: 0x1800e55f0
#pragma pack(push, 1)
struct S_TopicToSubchapter {
    uint8_t _rowbase[4];  // 0x000
    int32_t start_topic;  // 0x004  // PK
};
#pragma pack(pop)
static_assert(sizeof(S_TopicToSubchapter) == 8, "Size mismatch for S_TopicToSubchapter");

}  // namespace wh::databasemodule
