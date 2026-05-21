#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "skiptime"  row_size: 29
// Registration: 0x18014b610
#pragma pack(push, 1)
struct S_SkipTime {
    uint8_t _rowbase[4];  // 0x000
    int32_t skiptime_id;  // 0x004  // PK
    const char* skiptime_name;  // 0x008
    uint8_t _pad_0x010[8];
    int32_t skiptime_type_id;  // 0x018
    bool code_only;  // 0x01C
};
#pragma pack(pop)
static_assert(sizeof(S_SkipTime) == 29, "Size mismatch for S_SkipTime");

}  // namespace wh::databasemodule
