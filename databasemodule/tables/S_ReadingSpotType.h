#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "reading_spot_type"  row_size: 8
// Registration: 0x18011f860
#pragma pack(push, 1)
struct S_ReadingSpotType {
    uint8_t _rowbase[4];  // 0x000
    int32_t reading_spot_type_id;  // 0x004  // PK
};
#pragma pack(pop)
static_assert(sizeof(S_ReadingSpotType) == 8, "Size mismatch for S_ReadingSpotType");

}  // namespace wh::databasemodule
