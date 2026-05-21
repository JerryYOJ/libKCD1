#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "rpg_movement_type"  row_size: 40
// Registration: 0x180136ca0
#pragma pack(push, 1)
struct S_RpgMovementTypeTableRow {
    uint8_t _rowbase[4];  // 0x000
    int32_t rpg_movement_type_id;  // 0x004  // PK
    const char* rpg_movement_type_name;  // 0x008
    float stamina_regen;  // 0x010
    bool stamina_regen_is_relative;  // 0x014
    uint8_t _pad_0x015[3];
    float armor_load_to_regen;  // 0x018
    float armor_load_to_speed;  // 0x01C
    float visibility_penalization;  // 0x020
    float min_surface_speed_multiplier;  // 0x024
};
#pragma pack(pop)
static_assert(sizeof(S_RpgMovementTypeTableRow) == 40, "Size mismatch for S_RpgMovementTypeTableRow");

}  // namespace wh::databasemodule
