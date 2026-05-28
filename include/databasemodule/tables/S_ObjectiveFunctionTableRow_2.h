#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "objective_function"  row_size: 32
// Registration: 0x180153ee0
#pragma pack(push, 1)
struct S_ObjectiveFunctionTableRow_2 {
    uint8_t _rowbase[4];  // 0x000
    int32_t objective_function_id;  // 0x004  // PK
    // int32_t objective_id;  // 0x004 (alias)  // PK
    // int32_t quest_id;  // 0x004 (alias)  // PK
    // int32_t parameter_id;  // 0x004 (alias)  // PK
    uint8_t _pad_0x008[4];
    int32_t quest_asset_id;  // 0x00C
    uint8_t _pad_0x010[8];
    const char* value;  // 0x018
};
#pragma pack(pop)
static_assert(sizeof(S_ObjectiveFunctionTableRow_2) == 32, "Size mismatch for S_ObjectiveFunctionTableRow_2");

}  // namespace wh::databasemodule
