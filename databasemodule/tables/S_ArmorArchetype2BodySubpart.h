#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "armor_archetype"  row_size: 13
// Registration: 0x1800fe890
#pragma pack(push, 1)
struct S_ArmorArchetype2BodySubpart {
    uint8_t _rowbase[4];  // 0x000
    int32_t armor_archetype_id;  // 0x004  // PK
    // int32_t body_subpart_id;  // 0x004 (alias)  // PK
    int32_t body_layer_id;  // 0x008
    bool is_exclusive;  // 0x00C
};
#pragma pack(pop)
static_assert(sizeof(S_ArmorArchetype2BodySubpart) == 13, "Size mismatch for S_ArmorArchetype2BodySubpart");

}  // namespace wh::databasemodule
