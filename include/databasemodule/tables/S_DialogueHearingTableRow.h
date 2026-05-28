#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "dialogue_hearing"  row_size: 16
// Registration: 0x1800e2040
#pragma pack(push, 1)
struct S_DialogueHearingTableRow {
    uint8_t _rowbase[4];  // 0x000
    int32_t dialogue_hearing_id;  // 0x004  // PK
    const char* dialogue_hearing_name;  // 0x008
};
#pragma pack(pop)
static_assert(sizeof(S_DialogueHearingTableRow) == 16, "Size mismatch for S_DialogueHearingTableRow");

}  // namespace wh::databasemodule
