#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "function_name"  row_size: 16
// Registration: 0x1800e18c0
#pragma pack(push, 1)
struct S_FunctionNameTableRow {
    uint8_t _rowbase[8];  // 0x000
    const char* function_name;  // 0x008  // PK
    // const char* expression;  // 0x008 (alias)
};
#pragma pack(pop)
static_assert(sizeof(S_FunctionNameTableRow) == 16, "Size mismatch for S_FunctionNameTableRow");

}  // namespace wh::databasemodule
