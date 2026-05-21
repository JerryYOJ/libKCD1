#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "metarole"  row_size: 16
// Registration: 0x180136a50
#pragma pack(push, 1)
struct S_MetaroleTableRow_2 {
    uint8_t _rowbase[4];  // 0x000
    int32_t metarole_id;  // 0x004  // PK
    const char* metarole_name;  // 0x008
};
#pragma pack(pop)
static_assert(sizeof(S_MetaroleTableRow_2) == 16, "Size mismatch for S_MetaroleTableRow_2");

}  // namespace wh::databasemodule
