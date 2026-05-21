#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "exp_change"  row_size: 8
// Registration: 0x18014eef0
#pragma pack(push, 1)
struct S_ExpChange {
    uint8_t _rowbase[4];  // 0x000
    int32_t exp_change_id;  // 0x004  // PK
};
#pragma pack(pop)
static_assert(sizeof(S_ExpChange) == 8, "Size mismatch for S_ExpChange");

}  // namespace wh::databasemodule
