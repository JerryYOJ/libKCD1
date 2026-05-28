#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "reputation_condition"  row_size: 8
// Registration: 0x180120180
#pragma pack(push, 1)
struct S_ReputationCondition {
    uint8_t _rowbase[4];  // 0x000
    int32_t reputation_condition_id;  // 0x004  // PK
};
#pragma pack(pop)
static_assert(sizeof(S_ReputationCondition) == 8, "Size mismatch for S_ReputationCondition");

}  // namespace wh::databasemodule
