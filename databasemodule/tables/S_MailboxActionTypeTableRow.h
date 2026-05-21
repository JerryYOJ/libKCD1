#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "mailbox_action_type"  row_size: 16
// Registration: 0x1801d49b0
#pragma pack(push, 1)
struct S_MailboxActionTypeTableRow {
    uint8_t _rowbase[4];  // 0x000
    int32_t mailbox_action_type_id;  // 0x004  // PK
    const char* mailbox_action_type_name;  // 0x008
};
#pragma pack(pop)
static_assert(sizeof(S_MailboxActionTypeTableRow) == 16, "Size mismatch for S_MailboxActionTypeTableRow");

}  // namespace wh::databasemodule
