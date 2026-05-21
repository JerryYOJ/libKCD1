#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "brain_sensor"  row_size: 60
// Registration: 0x1801d7530
#pragma pack(push, 1)
struct S_BrainSensorTableRow {
    uint8_t _rowbase[16];  // 0x000
    uint64_t brain_sensor_id;  // 0x010  // PK
    // const char* brain_sensor_name;  // 0x010 (alias)
    int32_t brain_sensor_type;  // 0x018
    float range;  // 0x01C
    float field_of_view;  // 0x020
    float direction_x;  // 0x024
    float direction_y;  // 0x028
    float direction_z;  // 0x02C
    float position_x;  // 0x030
    float position_y;  // 0x034
    float position_z;  // 0x038
};
#pragma pack(pop)
static_assert(sizeof(S_BrainSensorTableRow) == 60, "Size mismatch for S_BrainSensorTableRow");

}  // namespace wh::databasemodule
