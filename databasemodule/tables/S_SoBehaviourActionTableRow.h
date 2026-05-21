#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "so_behaviour_action"  row_size: 16
// Registration: 0x1801dd300
#pragma pack(push, 1)
struct S_SoBehaviourActionTableRow {
    uint8_t _rowbase[4];  // 0x000
    int32_t so_behaviour_action_id;  // 0x004  // PK
    const char* so_behaviour_action_name;  // 0x008
};
#pragma pack(pop)
static_assert(sizeof(S_SoBehaviourActionTableRow) == 16, "Size mismatch for S_SoBehaviourActionTableRow");

}  // namespace wh::databasemodule
