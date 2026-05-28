#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "name"  row_size: 16
// Registration: 0x18010f300
#pragma pack(push, 1)
struct S_NameTableRow {
    uint8_t _rowbase[8];  // 0x000
    const char* name;  // 0x008  // PK
};
#pragma pack(pop)
static_assert(sizeof(S_NameTableRow) == 16, "Size mismatch for S_NameTableRow");

}  // namespace wh::databasemodule
