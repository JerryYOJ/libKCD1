#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "special_riposte"  row_size: 24
// Registration: 0x18011ec70
#pragma pack(push, 1)
struct S_SpecialRiposteTableRow {
    uint8_t _rowbase[4];  // 0x000
    int32_t special_riposte_id;  // 0x004  // PK
    uint8_t _pad_0x008[8];
    uint64_t perk_id;  // 0x010  // PK
};
#pragma pack(pop)
static_assert(sizeof(S_SpecialRiposteTableRow) == 24, "Size mismatch for S_SpecialRiposteTableRow");

}  // namespace wh::databasemodule
