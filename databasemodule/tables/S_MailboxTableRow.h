#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "mailbox"  row_size: 32
// Registration: 0x1801d4c00
#pragma pack(push, 1)
struct S_MailboxTableRow {
    uint8_t _rowbase[16];  // 0x000
    uint64_t mailbox_id;  // 0x010  // PK
    // const char* mailbox_name;  // 0x010 (alias)
    int32_t on_accept;  // 0x018
    int32_t message_limit;  // 0x01C
};
#pragma pack(pop)
static_assert(sizeof(S_MailboxTableRow) == 32, "Size mismatch for S_MailboxTableRow");

}  // namespace wh::databasemodule
