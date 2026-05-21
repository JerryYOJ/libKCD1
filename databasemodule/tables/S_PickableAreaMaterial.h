#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "material_name"  row_size: 16
// Registration: 0x18010d530
#pragma pack(push, 1)
struct S_PickableAreaMaterial {
    uint8_t _rowbase[8];  // 0x000
    const char* material_name;  // 0x008  // PK
    // --- virtual columns (offset=-1, not in struct memory) ---
    // int32_t pickable_area_id;
};
#pragma pack(pop)
static_assert(sizeof(S_PickableAreaMaterial) == 16, "Size mismatch for S_PickableAreaMaterial");

}  // namespace wh::databasemodule
