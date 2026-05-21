#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "mailbox_filter"  row_size: 40
// Registration: 0x1801d5030
#pragma pack(push, 1)
struct S_MailboxFilterTableRow {
    uint8_t _rowbase[16];  // 0x000
    uint64_t mailbox_filter_id;  // 0x010  // PK
    // CryGUID mailbox_id;  // 0x010 (alias)
    uint8_t _pad_0x018[8];
    const char* type;  // 0x020
};
#pragma pack(pop)
static_assert(sizeof(S_MailboxFilterTableRow) == 40, "Size mismatch for S_MailboxFilterTableRow");

}  // namespace wh::databasemodule
