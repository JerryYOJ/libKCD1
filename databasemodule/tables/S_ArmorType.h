#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "armor_type"  row_size: 16
// Registration: 0x1800feca0
#pragma pack(push, 1)
struct S_ArmorType {
    uint8_t _rowbase[4];  // 0x000
    int32_t armor_type_id;  // 0x004  // PK
    const char* armor_type_name;  // 0x008
};
#pragma pack(pop)
static_assert(sizeof(S_ArmorType) == 16, "Size mismatch for S_ArmorType");

}  // namespace wh::databasemodule
