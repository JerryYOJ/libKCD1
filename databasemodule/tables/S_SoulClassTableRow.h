#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "soul_class"  row_size: 52
// Registration: 0x180139b10
#pragma pack(push, 1)
struct S_SoulClassTableRow {
    uint8_t _rowbase[4];  // 0x000
    int32_t soul_class_id;  // 0x004  // PK
    const char* soul_class_name;  // 0x008
    CryGUID default_inventory_preset_id;  // 0x010
    bool postpone_default_inventory_preset;  // 0x020
    uint8_t _pad_0x021[3];
    float soul_class_courage;  // 0x024
    float hunting_coef;  // 0x028
    uint8_t _pad_0x02C[4];
    float hunting_capacity_cost;  // 0x030
};
#pragma pack(pop)
static_assert(sizeof(S_SoulClassTableRow) == 52, "Size mismatch for S_SoulClassTableRow");

}  // namespace wh::databasemodule
