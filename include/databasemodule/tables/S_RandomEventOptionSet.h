#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "random_event_option_set"  row_size: 16
// Registration: 0x18014adf0
#pragma pack(push, 1)
struct S_RandomEventOptionSet {
    uint8_t _rowbase[4];  // 0x000
    int32_t random_event_option_set_id;  // 0x004  // PK
    const char* random_event_option_set_name;  // 0x008
};
#pragma pack(pop)
static_assert(sizeof(S_RandomEventOptionSet) == 16, "Size mismatch for S_RandomEventOptionSet");

}  // namespace wh::databasemodule
