#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "inventory_preset"  row_size: 52
// Registration: 0x1800fde80
#pragma pack(push, 1)
struct S_InventoryPresetTableRow_2 {
    uint8_t _rowbase[16];  // 0x000
    uint64_t inventory_preset_id;  // 0x010  // PK
    // uint64_t item_id;  // 0x010 (alias)  // PK
    uint8_t _pad_0x018[8];
    int32_t amount;  // 0x020
    int32_t amount_random_add;  // 0x024
    float health;  // 0x028
    float health_offset;  // 0x02C
    float priority;  // 0x030
};
#pragma pack(pop)
static_assert(sizeof(S_InventoryPresetTableRow_2) == 52, "Size mismatch for S_InventoryPresetTableRow_2");

}  // namespace wh::databasemodule
