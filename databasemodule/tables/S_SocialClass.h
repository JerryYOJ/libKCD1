#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "social_class"  row_size: 32
// Registration: 0x180123940
#pragma pack(push, 1)
struct S_SocialClass {
    uint8_t _rowbase[4];  // 0x000
    int32_t social_class_id;  // 0x004  // PK
    const char* social_class_name;  // 0x008
    int32_t wealth;  // 0x010
    int32_t soul_crime_role_id;  // 0x014
    float preset_items_health_base;  // 0x018
    float preset_items_health_random;  // 0x01C
};
#pragma pack(pop)
static_assert(sizeof(S_SocialClass) == 32, "Size mismatch for S_SocialClass");

}  // namespace wh::databasemodule
