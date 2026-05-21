#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "so_behaviour_tag"  row_size: 40
// Registration: 0x1801dced0
#pragma pack(push, 1)
struct S_SoBehaviourTagTableRow {
    uint8_t _rowbase[16];  // 0x000
    uint64_t so_behaviour_tag_id;  // 0x010  // PK
    // int32_t navigation_agent_type;  // 0x010 (alias)
    const char* start_helper;  // 0x018
    const char* end_helper;  // 0x020
};
#pragma pack(pop)
static_assert(sizeof(S_SoBehaviourTagTableRow) == 40, "Size mismatch for S_SoBehaviourTagTableRow");

}  // namespace wh::databasemodule
