#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "combat_action_fragment_mapping"  row_size: 18
// Registration: 0x1800c6450
#pragma pack(push, 1)
struct S_CombatActionFragmentIdMappingTableRow {
    uint8_t _rowbase[4];  // 0x000
    int32_t combat_action_fragment_id_mapping_id;  // 0x004  // PK
    // int32_t action_type_id;  // 0x004 (alias)
    const char* fragment_id;  // 0x008
    bool preprocess_enabled;  // 0x010
    bool sync_hit;  // 0x011
};
#pragma pack(pop)
static_assert(sizeof(S_CombatActionFragmentIdMappingTableRow) == 18, "Size mismatch for S_CombatActionFragmentIdMappingTableRow");

}  // namespace wh::databasemodule
