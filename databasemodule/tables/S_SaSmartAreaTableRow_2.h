#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "sa_smart_area"  row_size: 24
// Registration: 0x1801dc030
#pragma pack(push, 1)
struct S_SaSmartAreaTableRow_2 {
    uint8_t _rowbase[16];  // 0x000
    uint64_t sa_smart_area_id;  // 0x010  // PK
    // uint64_t parent_tag_id;  // 0x010 (alias)  // PK
    // uint64_t child_tag_id;  // 0x010 (alias)  // PK
};
#pragma pack(pop)
static_assert(sizeof(S_SaSmartAreaTableRow_2) == 24, "Size mismatch for S_SaSmartAreaTableRow_2");

}  // namespace wh::databasemodule
