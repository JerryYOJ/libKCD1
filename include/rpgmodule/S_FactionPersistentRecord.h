#pragma once

#include <cstdint>
#include "S_FactionRecordEntry.h"

// ===========================================================================
// wh::rpgmodule::S_FactionPersistentRecord  -  element of C_Faction::m_persistentRecords.
// ===========================================================================
// Size 0x28 VERIFIED (deserialize sub_18119A218, save chunk tag 0x1EAC). Only the leading
// id read at +0x00 is solid; the embedded child entry and remaining names are INFERRED from
// the raw deserialize layout (one S_FactionRecordEntry built at record+0x08).
namespace wh::rpgmodule {

struct S_FactionPersistentRecord {
    uint32_t             m_id;       // +0x00  [VERIFIED read] record/key id
    uint8_t              _pad04[4];  // +0x04
    S_FactionRecordEntry m_entry;    // +0x08  [INFERRED] one inline child entry (0x20)
};
static_assert(sizeof(S_FactionPersistentRecord) == 0x28, "faction persistent record (save tag 0x1EAC)");

}  // namespace wh::rpgmodule
