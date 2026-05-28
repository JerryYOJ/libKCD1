#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "item"  row_size: 57
// Registration: 0x18010b600
#pragma pack(push, 1)
struct S_ItemTableRow_26 {
    uint8_t _rowbase[16];  // 0x000
    uint64_t item_id;  // 0x010  // PK
    // const char* holster_model;  // 0x010 (alias)
    const char* holster_material;  // 0x018
    int32_t weapon_class_id;  // 0x020
    uint8_t _pad_0x024[4];
    float defense;  // 0x028
    int32_t max_status;  // 0x02C
    int32_t str_req;  // 0x030
    int32_t agi_req;  // 0x034
    bool is_breakable;  // 0x038
};
#pragma pack(pop)
static_assert(sizeof(S_ItemTableRow_26) == 57, "Size mismatch for S_ItemTableRow_26");

}  // namespace wh::databasemodule
