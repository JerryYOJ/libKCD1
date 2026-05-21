#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "sequence"  row_size: 24
// Registration: 0x1800e48e0
#pragma pack(push, 1)
struct S_SequenceTableRow_3 {
    uint8_t _rowbase[4];  // 0x000
    int32_t sequence_id;  // 0x004  // PK
    // int32_t topic_id;  // 0x004 (alias)  // PK
    const char* entry_condition;  // 0x008
    const char* npc_entry_condition;  // 0x010
};
#pragma pack(pop)
static_assert(sizeof(S_SequenceTableRow_3) == 24, "Size mismatch for S_SequenceTableRow_3");

}  // namespace wh::databasemodule
