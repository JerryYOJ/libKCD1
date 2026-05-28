#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "rpg_param_key"  row_size: 16
// Registration: 0x18011eea0
#pragma pack(push, 1)
struct S_RpgParamKeyTableRow_2 {
    uint8_t _rowbase[8];  // 0x000
    const char* rpg_param_key;  // 0x008  // PK
    // float rpg_param_value;  // 0x008 (alias)
};
#pragma pack(pop)
static_assert(sizeof(S_RpgParamKeyTableRow_2) == 16, "Size mismatch for S_RpgParamKeyTableRow_2");

}  // namespace wh::databasemodule
