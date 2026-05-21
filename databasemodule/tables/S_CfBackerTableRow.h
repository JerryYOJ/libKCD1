#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "cf_backer"  row_size: 24
// Registration: 0x18010e360
#pragma pack(push, 1)
struct S_CfBackerTableRow {
    uint8_t _rowbase[4];  // 0x000
    int32_t cf_backer_id;  // 0x004  // PK
    const char* cf_backer_ingame_name;  // 0x008
    const char* calvary_cross_id;  // 0x010
};
#pragma pack(pop)
static_assert(sizeof(S_CfBackerTableRow) == 24, "Size mismatch for S_CfBackerTableRow");

}  // namespace wh::databasemodule
