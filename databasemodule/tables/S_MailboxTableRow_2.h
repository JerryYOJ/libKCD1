#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "mailbox"  row_size: 24
// Registration: 0x1801d9650
#pragma pack(push, 1)
struct S_MailboxTableRow_2 {
    uint8_t _rowbase[16];  // 0x000
    uint64_t mailbox_id;  // 0x010  // PK
    // int32_t priority;  // 0x010 (alias)
    // uint64_t situation_role_id;  // 0x010 (alias)  // PK
};
#pragma pack(pop)
static_assert(sizeof(S_MailboxTableRow_2) == 24, "Size mismatch for S_MailboxTableRow_2");

}  // namespace wh::databasemodule
