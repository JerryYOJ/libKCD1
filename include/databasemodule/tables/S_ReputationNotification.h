#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "reputation_notification"  row_size: 32
// Registration: 0x180120450
#pragma pack(push, 1)
struct S_ReputationNotification {
    uint8_t _rowbase[4];  // 0x000
    int32_t reputation_notification_id;  // 0x004  // PK
    const char* reputation_notification_name;  // 0x008
    const char* cooldown;  // 0x010
    const char* reputation_notification_ui_text;  // 0x018
};
#pragma pack(pop)
static_assert(sizeof(S_ReputationNotification) == 32, "Size mismatch for S_ReputationNotification");

}  // namespace wh::databasemodule
