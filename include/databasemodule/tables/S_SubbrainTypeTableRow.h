#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "subbrain_type"  row_size: 16
// Registration: 0x1801e1230
#pragma pack(push, 1)
struct S_SubbrainTypeTableRow {
    uint8_t _rowbase[4];  // 0x000
    int32_t subbrain_type_id;  // 0x004  // PK
    const char* subbrain_type_name;  // 0x008
};
#pragma pack(pop)
static_assert(sizeof(S_SubbrainTypeTableRow) == 16, "Size mismatch for S_SubbrainTypeTableRow");

}  // namespace wh::databasemodule
