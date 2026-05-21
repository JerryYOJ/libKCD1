#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "sa_behaviour_action"  row_size: 16
// Registration: 0x1801db060
#pragma pack(push, 1)
struct S_SaBehaviourActionTableRow {
    uint8_t _rowbase[4];  // 0x000
    int32_t sa_behaviour_action_id;  // 0x004  // PK
    const char* sa_behaviour_action_name;  // 0x008
};
#pragma pack(pop)
static_assert(sizeof(S_SaBehaviourActionTableRow) == 16, "Size mismatch for S_SaBehaviourActionTableRow");

}  // namespace wh::databasemodule
