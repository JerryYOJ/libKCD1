#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "hobby"  row_size: 16
// Registration: 0x18011a5b0
#pragma pack(push, 1)
struct S_Hobby {
    uint8_t _rowbase[4];  // 0x000
    int32_t hobby_id;  // 0x004  // PK
    const char* hobby_name;  // 0x008
};
#pragma pack(pop)
static_assert(sizeof(S_Hobby) == 16, "Size mismatch for S_Hobby");

}  // namespace wh::databasemodule
