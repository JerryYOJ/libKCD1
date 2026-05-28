#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "sleeping_spot_type"  row_size: 8
// Registration: 0x180123660
#pragma pack(push, 1)
struct S_SleepingSpotType {
    uint8_t _rowbase[4];  // 0x000
    int32_t sleeping_spot_type_id;  // 0x004  // PK
};
#pragma pack(pop)
static_assert(sizeof(S_SleepingSpotType) == 8, "Size mismatch for S_SleepingSpotType");

}  // namespace wh::databasemodule
