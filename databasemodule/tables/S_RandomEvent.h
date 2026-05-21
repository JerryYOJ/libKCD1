#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "random_event"  row_size: 48
// Registration: 0x180149a20
#pragma pack(push, 1)
struct S_RandomEvent {
    uint8_t _rowbase[4];  // 0x000
    int32_t random_event_id;  // 0x004  // PK
    const char* ui_caption;  // 0x008
    const char* condition_expression;  // 0x010
    float base_run_chance;  // 0x018
    float night_run_chance_modif;  // 0x01C
    float map_disappear_time;  // 0x020
    float map_game_speed;  // 0x024
    int32_t map_icon_id;  // 0x028
    int32_t random_event_option_set_id;  // 0x02C
};
#pragma pack(pop)
static_assert(sizeof(S_RandomEvent) == 48, "Size mismatch for S_RandomEvent");

}  // namespace wh::databasemodule
