#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "actor_action_fragment_mapping"  row_size: 17
// Registration: 0x1800ead80
#pragma pack(push, 1)
struct S_ActorActionFragmentIdMappingTableRow {
    uint8_t _rowbase[4];  // 0x000
    int32_t actor_action_fragment_id_mapping_id;  // 0x004  // PK
    // int32_t actor_action_type_id;  // 0x004 (alias)
    const char* fragment_id;  // 0x008
    bool preprocess_enabled;  // 0x010
};
#pragma pack(pop)
static_assert(sizeof(S_ActorActionFragmentIdMappingTableRow) == 17, "Size mismatch for S_ActorActionFragmentIdMappingTableRow");

}  // namespace wh::databasemodule
