#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "resource"  row_size: 32
// Registration: 0x1801466b0
#pragma pack(push, 1)
struct S_NewHomesResource {
    uint8_t _rowbase[4];  // 0x000
    int32_t resource_id;  // 0x004  // PK
    const char* resource_name;  // 0x008
    const char* ui_name;  // 0x010
    const char* ui_icon;  // 0x018
};
#pragma pack(pop)
static_assert(sizeof(S_NewHomesResource) == 32, "Size mismatch for S_NewHomesResource");

}  // namespace wh::databasemodule
