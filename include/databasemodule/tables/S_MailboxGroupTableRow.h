#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "mailbox_group"  row_size: 36
// Registration: 0x1801cfbb0
#pragma pack(push, 1)
struct S_MailboxGroupTableRow {
    uint8_t _rowbase[16];  // 0x000
    uint64_t mailbox_group_id;  // 0x010  // PK
    // uint64_t mailbox_id;  // 0x010 (alias)  // PK
    uint8_t _pad_0x018[8];
    int32_t priority;  // 0x020
};
#pragma pack(pop)
static_assert(sizeof(S_MailboxGroupTableRow) == 36, "Size mismatch for S_MailboxGroupTableRow");

}  // namespace wh::databasemodule
