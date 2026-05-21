#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "item"  row_size: 56
// Registration: 0x18010a2e0
#pragma pack(push, 1)
struct S_ItemTableRow_22 {
    uint8_t _rowbase[16];  // 0x000
    uint64_t item_id;  // 0x010  // PK
    // float weight;  // 0x010 (alias)
    // int32_t price;  // 0x014 (alias)
    const char* model;  // 0x018
    const char* material;  // 0x020
    const char* entity_script;  // 0x028
    float owner_fading_coef;  // 0x030
    float visibility_coef;  // 0x034
};
#pragma pack(pop)
static_assert(sizeof(S_ItemTableRow_22) == 56, "Size mismatch for S_ItemTableRow_22");

}  // namespace wh::databasemodule
