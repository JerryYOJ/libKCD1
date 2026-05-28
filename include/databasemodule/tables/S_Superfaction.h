#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "superfaction"  row_size: 24
// Registration: 0x180120d80
#pragma pack(push, 1)
struct S_Superfaction {
    uint8_t _rowbase[4];  // 0x000
    int32_t superfaction_id;  // 0x004  // PK
    const char* superfaction_name;  // 0x008
    const char* ui_name;  // 0x010
};
#pragma pack(pop)
static_assert(sizeof(S_Superfaction) == 24, "Size mismatch for S_Superfaction");

}  // namespace wh::databasemodule
