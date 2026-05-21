#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "situation"  row_size: 68
// Registration: 0x1801d8230
#pragma pack(push, 1)
struct S_SituationTableRow {
    uint8_t _rowbase[16];  // 0x000
    uint64_t situation_id;  // 0x010  // PK
    // CryGUID sa_smart_area_id;  // 0x010 (alias)
    uint8_t _pad_0x018[8];
    const char* name;  // 0x020
    CryGUID situation_frequency_id;  // 0x028
    int32_t search_type;  // 0x038
    bool enabled;  // 0x03C
    uint8_t _pad_0x03D[3];
    int32_t max_instances;  // 0x040
};
#pragma pack(pop)
static_assert(sizeof(S_SituationTableRow) == 68, "Size mismatch for S_SituationTableRow");

}  // namespace wh::databasemodule
