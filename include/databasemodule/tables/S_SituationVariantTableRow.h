#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "situation_variant"  row_size: 44
// Registration: 0x1801da8f0
#pragma pack(push, 1)
struct S_SituationVariantTableRow {
    uint8_t _rowbase[16];  // 0x000
    uint64_t situation_variant_id;  // 0x010  // PK
    // CryGUID situation_id;  // 0x010 (alias)
    uint8_t _pad_0x018[8];
    const char* name;  // 0x020
    int32_t order_by;  // 0x028
};
#pragma pack(pop)
static_assert(sizeof(S_SituationVariantTableRow) == 44, "Size mismatch for S_SituationVariantTableRow");

}  // namespace wh::databasemodule
