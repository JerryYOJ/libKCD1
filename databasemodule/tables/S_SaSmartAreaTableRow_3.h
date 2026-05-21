#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "sa_smart_area"  row_size: 40
// Registration: 0x1801dc370
#pragma pack(push, 1)
struct S_SaSmartAreaTableRow_3 {
    uint8_t _rowbase[16];  // 0x000
    uint64_t sa_smart_area_id;  // 0x010  // PK
    // const char* sa_smart_area_name;  // 0x010 (alias)
    CryGUID brain_id;  // 0x018
};
#pragma pack(pop)
static_assert(sizeof(S_SaSmartAreaTableRow_3) == 40, "Size mismatch for S_SaSmartAreaTableRow_3");

}  // namespace wh::databasemodule
