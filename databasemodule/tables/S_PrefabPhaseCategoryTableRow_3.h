#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "prefab_phase_category"  row_size: 16
// Registration: 0x1801fcc30
#pragma pack(push, 1)
struct S_PrefabPhaseCategoryTableRow_3 {
    uint8_t _rowbase[4];  // 0x000
    int32_t prefab_phase_category_id;  // 0x004  // PK
    // int32_t order;  // 0x004 (alias)  // PK
    const char* prefabfullname;  // 0x008
};
#pragma pack(pop)
static_assert(sizeof(S_PrefabPhaseCategoryTableRow_3) == 16, "Size mismatch for S_PrefabPhaseCategoryTableRow_3");

}  // namespace wh::databasemodule
