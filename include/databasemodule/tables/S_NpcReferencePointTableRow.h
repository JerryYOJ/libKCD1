#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "npc_reference_point"  row_size: 52
// Registration: 0x1801d6bf0
#pragma pack(push, 1)
struct S_NpcReferencePointTableRow {
    uint8_t _rowbase[16];  // 0x000
    uint64_t npc_reference_point_id;  // 0x010  // PK
    // const char* npc_reference_point_name;  // 0x010 (alias)
    int32_t priority;  // 0x018
    uint8_t _pad_0x01C[4];
    const char* bone_name;  // 0x020
    float coord_x;  // 0x028
    float coord_y;  // 0x02C
    float coord_z;  // 0x030
};
#pragma pack(pop)
static_assert(sizeof(S_NpcReferencePointTableRow) == 52, "Size mismatch for S_NpcReferencePointTableRow");

}  // namespace wh::databasemodule
