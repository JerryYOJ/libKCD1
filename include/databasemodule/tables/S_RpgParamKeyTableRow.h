#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "rpg_param_key"  row_size: 28
// Registration: 0x18011e2c0
#pragma pack(push, 1)
struct S_RpgParamKeyTableRow {
    uint8_t _rowbase[8];  // 0x000
    const char* rpg_param_key;  // 0x008  // PK
    uint64_t perk_id;  // 0x010  // PK
    float rpg_param_value;  // 0x018
};
#pragma pack(pop)
static_assert(sizeof(S_RpgParamKeyTableRow) == 28, "Size mismatch for S_RpgParamKeyTableRow");

}  // namespace wh::databasemodule
