#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "brain_sensor_type"  row_size: 16
// Registration: 0x1801d7fe0
#pragma pack(push, 1)
struct S_BrainSensorTypeTableRow {
    uint8_t _rowbase[4];  // 0x000
    int32_t brain_sensor_type_id;  // 0x004  // PK
    const char* brain_sensor_type_name;  // 0x008
};
#pragma pack(pop)
static_assert(sizeof(S_BrainSensorTypeTableRow) == 16, "Size mismatch for S_BrainSensorTypeTableRow");

}  // namespace wh::databasemodule
