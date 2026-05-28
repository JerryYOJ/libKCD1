#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "item"  row_size: 32
// Registration: 0x180105b30
#pragma pack(push, 1)
struct S_ItemTableRow_9 {
    uint8_t _rowbase[16];  // 0x000
    uint64_t item_id;  // 0x010  // PK
    // int32_t text_id;  // 0x010 (alias)
    // int32_t class_id;  // 0x014 (alias)
    uint8_t _pad_0x018[4];
    int32_t document_ui_layout;  // 0x01C
};
#pragma pack(pop)
static_assert(sizeof(S_ItemTableRow_9) == 32, "Size mismatch for S_ItemTableRow_9");

}  // namespace wh::databasemodule
