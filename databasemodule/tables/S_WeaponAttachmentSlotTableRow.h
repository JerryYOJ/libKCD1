#pragma once
#include "../database_types.h"

namespace wh::databasemodule {

// Table: "weapon_attachment_slot"  row_size: 16
// Registration: 0x18010b3b0
#pragma pack(push, 1)
struct S_WeaponAttachmentSlotTableRow {
    uint8_t _rowbase[4];  // 0x000
    int32_t weapon_attachment_slot_id;  // 0x004  // PK
    const char* weapon_attachment_slot_name;  // 0x008
};
#pragma pack(pop)
static_assert(sizeof(S_WeaponAttachmentSlotTableRow) == 16, "Size mismatch for S_WeaponAttachmentSlotTableRow");

}  // namespace wh::databasemodule
