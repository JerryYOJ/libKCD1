#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "random_event_option"  row_size: 72
// Registration: 0x18014a3a0
#pragma pack(push, 1)
struct S_RandomEventOption {
    uint8_t _rowbase[4];  // 0x000
    int32_t random_event_option_id;  // 0x004  // PK
    // int32_t random_event_option_set_id;  // 0x004 (alias)
    int32_t random_event_source_type_id;  // 0x008
    uint8_t _pad_0x00C[4];
    const char* ui_caption;  // 0x010
    const char* condition_expression;  // 0x018
    const char* chance_expression;  // 0x020
    const char* success_cmd;  // 0x028
    const char* fail_cmd;  // 0x030
    const char* success_msg;  // 0x038
    const char* fail_msg;  // 0x040
};
#pragma pack(pop)
static_assert(sizeof(S_RandomEventOption) == 72, "Size mismatch for S_RandomEventOption");

}  // namespace wh::databasemodule
