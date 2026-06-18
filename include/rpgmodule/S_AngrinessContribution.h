#pragma once

#include <cstdint>
#include <cstddef>

// ===========================================================================
// wh::rpgmodule::S_AngrinessContribution  -  one entry tracking a contribution
// to a faction's angriness/morale value.
// ===========================================================================
// Element of the std::vector-like container embedded in the C_Faction angriness
// sub-object (C_Faction+0x18), whose storage control lives at C_Faction+0x1B0..
// Element stride is 0x18 [CONFIRMED]: the adder sub_18118F188 advances the end
// pointer by 0x18 per push and writes exactly these fields.
//
// Writer:  sub_18118F188(angrinessObj, amount, srcFaction, reason, flag)
//   amount           -> +0x00 (float)
//   srcFactionId     -> +0x04  computed as **(_DWORD**)(srcFaction+0x278), i.e. the
//                              source faction-def's id field (S_FactionDef+0x00).
//                              0 for AddAngriness (no source faction passed).
//   reason (char*)   -> +0x08
//   flag (byte)      -> +0x10
namespace wh::rpgmodule {

struct S_AngrinessContribution {
    float       amount;             // +0x00  [CONFIRMED] signed angriness delta
    int32_t     sourceFactionId;    // +0x04  [CONFIRMED] source faction id (S_FactionDef.id), 0 if none
    const char* reason;             // +0x08  [CONFIRMED] interned string literal (e.g. "Set programatically.")
    uint8_t     flag;               // +0x10  [CONFIRMED] byte flag (1 in the programmatic-set path)
    uint8_t     _pad11[7];          // +0x11  padding to 0x18 element stride
};
static_assert(sizeof(S_AngrinessContribution) == 0x18, "S_AngrinessContribution size");

}  // namespace wh::rpgmodule
