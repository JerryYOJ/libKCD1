#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "random_event_option_set"  row_size: 36
// Registration: 0x18014b020
#pragma pack(push, 1)
struct S_RandomEventOptionSetTableRow {
    uint8_t _rowbase[4];  // 0x000
    int32_t random_event_option_set_id;  // 0x004  // PK
    // int32_t random_event_source_type_id;  // 0x004 (alias)  // PK
    const char* random_event_variant_id;  // 0x008  // PK
    const char* ui_caption;  // 0x010
    const char* ui_description;  // 0x018
    int32_t map_icon_id;  // 0x020
};
#pragma pack(pop)
static_assert(sizeof(S_RandomEventOptionSetTableRow) == 36, "Size mismatch for S_RandomEventOptionSetTableRow");

}  // namespace wh::databasemodule
