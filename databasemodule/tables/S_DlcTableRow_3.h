#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "dlc"  row_size: 8
// Registration: 0x1801fc010
#pragma pack(push, 1)
struct S_DlcTableRow_3 {
    uint8_t _rowbase[4];  // 0x000
    int32_t dlc_id;  // 0x004  // PK
    // bool affects_savegame;  // 0x004 (alias)
    // bool need_mount;  // 0x005 (alias)
};
#pragma pack(pop)
static_assert(sizeof(S_DlcTableRow_3) == 8, "Size mismatch for S_DlcTableRow_3");

}  // namespace wh::databasemodule
