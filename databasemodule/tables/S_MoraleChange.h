#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "morale_change"  row_size: 8
// Registration: 0x18011b590
#pragma pack(push, 1)
struct S_MoraleChange {
    uint8_t _rowbase[4];  // 0x000
    int32_t morale_change_id;  // 0x004  // PK
};
#pragma pack(pop)
static_assert(sizeof(S_MoraleChange) == 8, "Size mismatch for S_MoraleChange");

}  // namespace wh::databasemodule
