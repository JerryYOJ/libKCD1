#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "horse_irritation"  row_size: 8
// Registration: 0x18011a7e0
#pragma pack(push, 1)
struct S_HorseIrritation {
    uint8_t _rowbase[4];  // 0x000
    int32_t horse_irritation_id;  // 0x004  // PK
    // int32_t morale_change_id;  // 0x004 (alias)
};
#pragma pack(pop)
static_assert(sizeof(S_HorseIrritation) == 8, "Size mismatch for S_HorseIrritation");

}  // namespace wh::databasemodule
