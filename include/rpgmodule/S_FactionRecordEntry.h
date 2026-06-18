#pragma once

#include <cstdint>
#include "../framework/WUID.h"

// ===========================================================================
// wh::rpgmodule::S_FactionRecordEntry  -  child entry of S_FactionPersistentRecord.
// ===========================================================================
// Size 0x20 VERIFIED (deserialize child reader sub_180A99970, save chunk tag 0x5DA).
// FIELD NAMES INFERRED from the raw read widths/offsets only -- not from any accessor.
// The +0x10 qword is read via the dedicated 8-byte helper sub_180F34634 (vs the generic
// sub_180F34668), so it is plausibly a wh::framework::WUID; this is UNVERIFIED.
namespace wh::rpgmodule {

struct S_FactionRecordEntry {
    uint32_t            m_field00;   // +0x00  [INFERRED] 4-byte read
    uint8_t             m_field04;   // +0x04  [INFERRED] 1-byte read
    uint8_t             m_field05;   // +0x05  [INFERRED] 1-byte read
    uint8_t             _pad06[2];   // +0x06
    uint32_t            m_field08;   // +0x08  [INFERRED] 4-byte read
    uint8_t             _pad0C[4];   // +0x0C
    wh::framework::WUID m_wuid;      // +0x10  [INFERRED] 8-byte read via sub_180F34634 (WUID identity unverified)
    uint32_t            m_field18;   // +0x18  [INFERRED] 4-byte read
    uint32_t            m_field1C;   // +0x1C  [INFERRED] 4-byte read
};
static_assert(sizeof(S_FactionRecordEntry) == 0x20, "faction record child entry (sub_180A99970)");

}  // namespace wh::rpgmodule
