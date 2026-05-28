#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "situation_frequency"  row_size: 48
// Registration: 0x1801d8930
#pragma pack(push, 1)
struct S_SituationFrequencyTableRow {
    uint8_t _rowbase[16];  // 0x000
    uint64_t situation_frequency_id;  // 0x010  // PK
    // const char* name;  // 0x010 (alias)
    int32_t global_minimal_interval;  // 0x018
    int32_t global_interval_variation;  // 0x01C
    bool b_global_variation_per_npc;  // 0x020
    uint8_t _pad_0x021[3];
    int32_t local_minimal_interval;  // 0x024
    int32_t local_interval_variation;  // 0x028
    int32_t time_type;  // 0x02C
};
#pragma pack(pop)
static_assert(sizeof(S_SituationFrequencyTableRow) == 48, "Size mismatch for S_SituationFrequencyTableRow");

}  // namespace wh::databasemodule
