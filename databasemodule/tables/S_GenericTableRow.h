#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "%s"  row_size: 16
// Registration: 0x1800afb40
#pragma pack(push, 1)
struct S_GenericTableRow {
    uint8_t _rowbase[4];  // 0x000
    int32_t _s_id;  // 0x004  // PK
    const char* _s_name;  // 0x008
};
#pragma pack(pop)
static_assert(sizeof(S_GenericTableRow) == 16, "Size mismatch for S_GenericTableRow");

}  // namespace wh::databasemodule
