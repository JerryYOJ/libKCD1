#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "so_behaviour_state"  row_size: 16
// Registration: 0x1801dd550
#pragma pack(push, 1)
struct S_SoBehaviourStateTableRow {
    uint8_t _rowbase[4];  // 0x000
    int32_t so_behaviour_state_id;  // 0x004  // PK
    const char* so_behaviour_state_name;  // 0x008
};
#pragma pack(pop)
static_assert(sizeof(S_SoBehaviourStateTableRow) == 16, "Size mismatch for S_SoBehaviourStateTableRow");

}  // namespace wh::databasemodule
