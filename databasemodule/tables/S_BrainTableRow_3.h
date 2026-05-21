#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "brain"  row_size: 36
// Registration: 0x1801d3200
#pragma pack(push, 1)
struct S_BrainTableRow_3 {
    uint8_t _rowbase[16];  // 0x000
    uint64_t brain_id;  // 0x010  // PK
    // uint64_t subbrain_id;  // 0x010 (alias)  // PK
    uint8_t _pad_0x018[8];
    int32_t priority;  // 0x020
};
#pragma pack(pop)
static_assert(sizeof(S_BrainTableRow_3) == 36, "Size mismatch for S_BrainTableRow_3");

}  // namespace wh::databasemodule
