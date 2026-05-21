#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "so_smart_object"  row_size: 24
// Registration: 0x1801de3a0
#pragma pack(push, 1)
struct S_SoSmartObjectTableRow_2 {
    uint8_t _rowbase[16];  // 0x000
    uint64_t so_smart_object_id;  // 0x010  // PK
    // uint64_t parent_tag_id;  // 0x010 (alias)  // PK
    // uint64_t child_tag_id;  // 0x010 (alias)  // PK
};
#pragma pack(pop)
static_assert(sizeof(S_SoSmartObjectTableRow_2) == 24, "Size mismatch for S_SoSmartObjectTableRow_2");

}  // namespace wh::databasemodule
