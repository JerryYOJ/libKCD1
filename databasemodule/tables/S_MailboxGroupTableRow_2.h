#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "mailbox_group"  row_size: 32
// Registration: 0x1801cfed0
#pragma pack(push, 1)
struct S_MailboxGroupTableRow_2 {
    uint8_t _rowbase[16];  // 0x000
    uint64_t mailbox_group_id;  // 0x010  // PK
    // const char* mailbox_group_file_name;  // 0x010 (alias)
    const char* mailbox_group_tree_name;  // 0x018
};
#pragma pack(pop)
static_assert(sizeof(S_MailboxGroupTableRow_2) == 32, "Size mismatch for S_MailboxGroupTableRow_2");

}  // namespace wh::databasemodule
