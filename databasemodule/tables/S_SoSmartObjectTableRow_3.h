#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "so_smart_object"  row_size: 56
// Registration: 0x1801de700
#pragma pack(push, 1)
struct S_SoSmartObjectTableRow_3 {
    uint8_t _rowbase[16];  // 0x000
    uint64_t so_smart_object_id;  // 0x010  // PK
    // const char* so_smart_object_name;  // 0x010 (alias)
    CryGUID brain_id;  // 0x018
    CryGUID body_id;  // 0x028
};
#pragma pack(pop)
static_assert(sizeof(S_SoSmartObjectTableRow_3) == 56, "Size mismatch for S_SoSmartObjectTableRow_3");

}  // namespace wh::databasemodule
