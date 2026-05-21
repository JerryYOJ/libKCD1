#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "metarole"  row_size: 24
// Registration: 0x180124160
#pragma pack(push, 1)
struct S_MetaroleTableRow {
    uint8_t _rowbase[4];  // 0x000
    int32_t metarole_id;  // 0x004  // PK
    uint8_t _pad_0x008[8];
    uint64_t soul_id;  // 0x010  // PK
};
#pragma pack(pop)
static_assert(sizeof(S_MetaroleTableRow) == 24, "Size mismatch for S_MetaroleTableRow");

}  // namespace wh::databasemodule
