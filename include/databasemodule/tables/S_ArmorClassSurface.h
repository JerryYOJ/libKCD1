#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "armor_class"  row_size: 20
// Registration: 0x1801170f0
#pragma pack(push, 1)
struct S_ArmorClassSurface {
    uint8_t _rowbase[4];  // 0x000
    int32_t armor_class_id;  // 0x004  // PK
    const char* engine_surface_name;  // 0x008
    float engine_surface_priority_multiplier;  // 0x010
};
#pragma pack(pop)
static_assert(sizeof(S_ArmorClassSurface) == 20, "Size mismatch for S_ArmorClassSurface");

}  // namespace wh::databasemodule
