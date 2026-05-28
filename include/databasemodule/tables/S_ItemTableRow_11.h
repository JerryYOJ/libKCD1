#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "item"  row_size: 100
// Registration: 0x180106af0
#pragma pack(push, 1)
struct S_ItemTableRow_11 {
    uint8_t _rowbase[16];  // 0x000
    uint64_t item_id;  // 0x010  // PK
    // float health_benefit;  // 0x010 (alias)
    // float refresh_benefit;  // 0x014 (alias)
    float nutrition_benefit;  // 0x018
    float short_term_nutrition_benefit_ratio;  // 0x01C
    float alcohol_content;  // 0x020
    int32_t max_status;  // 0x024
    int32_t food_type_id;  // 0x028
    int32_t food_subtype_id;  // 0x02C
    uint8_t _pad_0x030[48];
    float decay_time_hours;  // 0x060
    // --- virtual columns (offset=-1, not in struct memory) ---
    // uint64_t cooked_item_id;
    // uint64_t smoked_item_id;
    // uint64_t dried_item_id;
};
#pragma pack(pop)
static_assert(sizeof(S_ItemTableRow_11) == 100, "Size mismatch for S_ItemTableRow_11");

}  // namespace wh::databasemodule
