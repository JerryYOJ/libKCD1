#pragma once

#include <cstdint>
#include <cstddef>

#include "../framework/WUID.h"
#include "E_ReputationChangeTarget.h"

// ===========================================================================
// wh::rpgmodule::S_ReputationChangeEntry  -  the 0x20-byte change descriptor
// ("ChangeStruct") passed to the faction reputation writer.
// ===========================================================================
// Built on the stack by the immediate path C_FactionReputationEffect::Apply
// (sub_18117E2AC) and consumed by ApplyReputationToFaction (sub_18118F47C):
//   v13 (float) @ +0x00 = RPGParams[0x1CB] * row.change      (scaledChange)
//   v14 (byte)  @ +0x04 = row.target  (E_ReputationChangeTarget)
//   v15 (byte)  @ +0x05 = row.can_change_hostility
//   v16 (int)   @ +0x08 = 0x3F800000 (1.0f delayMult)
//   v17 (qword) @ +0x10 = cause WUID  (sub_18118F47C reads it as a WUID for soul lookup)
//   v18 (int)   @ +0x18 = changeId
//   v19 (int)   @ +0x1C = 0  (or the 1-prox weight in the nearby-spread path)
// The writer dispatches on targetBitmask: &0x02 faction (C_Faction+0x10), &0x08
// nearby spread, &0x04 superfaction.
namespace wh::rpgmodule {

struct S_ReputationChangeEntry {
    float                     scaledChange;        // +0x00  [CONFIRMED] change * ReputationPropagationCoef(0.3)
    E_ReputationChangeTarget  targetBitmask;       // +0x04  [CONFIRMED] which layers to affect
    uint8_t                   canChangeHostility;  // +0x05  [CONFIRMED] sign mode (allow crossing zero)
    uint8_t                   _pad06[2];           // +0x06
    float                     delayMult;           // +0x08  [CONFIRMED] 1.0 immediate; 1-prox in nearby spread
    uint8_t                   _pad0C[4];           // +0x0C
    wh::framework::WUID       cause;               // +0x10  [CONFIRMED] cause soul WUID (read for LookupByWUID)
    int32_t                   changeId;            // +0x18  [CONFIRMED] reputation_change row id
    int32_t                   weightOrZero;        // +0x1C  [CONFIRMED] 0 immediate; proximity weight in nearby
};
static_assert(sizeof(S_ReputationChangeEntry) == 0x20, "S_ReputationChangeEntry size");

}  // namespace wh::rpgmodule
