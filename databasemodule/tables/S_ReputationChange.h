#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "reputation_change"  row_size: 32
// Registration: 0x18011fb40
#pragma pack(push, 1)
struct S_ReputationChange {
    uint8_t _rowbase[4];  // 0x000
    int32_t reputation_change_id;  // 0x004  // PK
    uint8_t _pad_0x008[8];
    float change;  // 0x010
    int32_t reputation_change_target_id;  // 0x014
    bool can_change_hostility;  // 0x018
    uint8_t _pad_0x019[3];
    float reputation_cap;  // 0x01C
};
#pragma pack(pop)
static_assert(sizeof(S_ReputationChange) == 32, "Size mismatch for S_ReputationChange");

}  // namespace wh::databasemodule
