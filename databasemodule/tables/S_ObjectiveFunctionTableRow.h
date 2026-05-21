#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "objective_function"  row_size: 48
// Registration: 0x1801537e0
#pragma pack(push, 1)
struct S_ObjectiveFunctionTableRow {
    uint8_t _rowbase[4];  // 0x000
    int32_t objective_function_id;  // 0x004  // PK
    // int32_t objective_id;  // 0x004 (alias)  // PK
    // int32_t quest_id;  // 0x004 (alias)  // PK
    uint8_t _pad_0x008[4];
    int32_t objective_function_type_id;  // 0x00C
    CryGUID context_soul_id;  // 0x010
    bool call_script;  // 0x020
    uint8_t _pad_0x021[7];
    const char* function;  // 0x028
};
#pragma pack(pop)
static_assert(sizeof(S_ObjectiveFunctionTableRow) == 48, "Size mismatch for S_ObjectiveFunctionTableRow");

}  // namespace wh::databasemodule
