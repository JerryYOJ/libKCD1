#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "inventory"  row_size: 24
// Registration: 0x180123f30
#pragma pack(push, 1)
struct S_InventoryTableRow_4 {
    uint8_t _rowbase[16];  // 0x000
    uint64_t inventory_id;  // 0x010  // PK
    // uint64_t soul_id;  // 0x010 (alias)  // PK
};
#pragma pack(pop)
static_assert(sizeof(S_InventoryTableRow_4) == 24, "Size mismatch for S_InventoryTableRow_4");

}  // namespace wh::databasemodule
