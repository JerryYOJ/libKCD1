#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "item_class"  row_size: 40
// Registration: 0x1801d4670
#pragma pack(push, 1)
struct S_ItemClassTableRow {
    uint8_t _rowbase[16];  // 0x000
    uint64_t item_class_id;  // 0x010  // PK
    // CryGUID so_smart_object_id;  // 0x010 (alias)
    uint8_t _pad_0x018[8];
    const char* helper_set_name;  // 0x020
};
#pragma pack(pop)
static_assert(sizeof(S_ItemClassTableRow) == 40, "Size mismatch for S_ItemClassTableRow");

}  // namespace wh::databasemodule
