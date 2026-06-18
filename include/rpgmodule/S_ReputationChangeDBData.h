#pragma once

#include <cstdint>
#include <cstddef>

#include "E_ReputationChangeTarget.h"
// CryStringT<char> is provided by the PCH prelude (CryString.h is in PCH.h), as in
// S_InformationRecord.h. The string field below uses it without a per-header include.

// ===========================================================================
// wh::rpgmodule::S_ReputationChangeDBData  -  runtime row of the
// `reputation_change` table (the data POD inside the C_ObjectTableDatabase).
// ===========================================================================
// DB type: C_ObjectDatabaseIdIndexed<C_ObjectTableDatabase<S_ReputationChange,
//          S_ReputationChangeDBData>, int> (ctor sub_1811704FC).
// Element stride 0x20 [CONFIRMED]: the name-keyed scanner sub_180A9D5E0 advances
// by 0x20 per row and reads the name at *(row+0x08).
// Lookup-by-id sub_18117EAD8 returns S_ReputationChangeDBData* from the pointer
// array qword_1835AA3B8 (id - dword_1835AA3D0).
//
// IMPORTANT: this is the RUNTIME repacked row, distinct from the auto-generated
// alphabetized-XML schema struct wh::databasemodule::S_ReputationChange (which is
// WIDER: change@+0x10, target_id@+0x14, can_change_hostility@+0x18(byte),
// reputation_cap@+0x1C(float), reputation_notification_id@+0x20). The runtime
// layout below (id@+0x00, hostility byte-compacted to +0x15) is what the engine
// actually reads in sub_18117E2AC / sub_18118F47C.
namespace wh::rpgmodule {

struct S_ReputationChangeDBData {
    int32_t                   reputation_change_id;          // +0x00  [INFERRED] id@0 (same packing as S_FactionDef.id)
    int32_t                   _pad04;                        // +0x04
    CryStringT<char>          name;                          // +0x08  [CONFIRMED offset; type INFERRED] row name (scanner sub_180A9D5E0)
    float                     change;                        // +0x10  [CONFIRMED] reputation delta (sub_18117E2AC)
    E_ReputationChangeTarget  reputation_change_target_id;   // +0x14  [CONFIRMED] target bitmask byte
    uint8_t                   can_change_hostility;          // +0x15  [CONFIRMED] sign/hostility byte
    uint8_t                   _pad16[2];                     // +0x16
    float                     reputation_cap;                // +0x18  [INFERRED] not consumed in the faction Apply path
    int32_t                   reputation_notification_id;    // +0x1C  [CONFIRMED] id-index used by sub_18119B650 (row+0x1C)
};
static_assert(sizeof(S_ReputationChangeDBData) == 0x20, "S_ReputationChangeDBData size");

}  // namespace wh::rpgmodule
