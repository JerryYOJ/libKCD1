#pragma once
#include <cstdint>

namespace wh::rpgmodule {

// ---------------------------------------------------------------------------
// E_CombatStat -- combat / automation perk-stat ids. Modifier category 2
// (C_Soul m_combatStatMods @ soul+0xA8). Built by the global ctor sub_1801282A0;
// code->id lookup is C_RPGUtils vtable +0x88 (not-found sentinel 0x27 = 39).
//
// These feed C_RPGCombat (sub_1802AE2F0) for the melee defense reaction weights
// (and other combat calcs), applied as multiplicative S_ModifierNode modifiers
// (E_ModifierOp MulBase '*' / MulCurrent '%'). This is a SEPARATE namespace from
// E_DerivedStat (category 3): here Pbs(8) is the perfect-block stat, not Hlt.
//
// Enumerator names are the verbatim 3-letter codes (the buff `params` keys), e.g.
// a buff "pbs*0.5" on an enemy soul halves its perfect-block AND master-strike
// chance, "dsl*0.5" halves dodge. Only a few meanings are pinned; the rest are raw
// codes [meaning UNVERIFIED].
// ---------------------------------------------------------------------------
enum class E_CombatStat : int32_t {
    Ade = 0x00,
    Uat = 0x01,
    Wat = 0x02,   // weapon attack time/speed (the Chain-strike buff scales this: "wat*1.1")
    Wac = 0x03,
    Ahm = 0x04,
    Rtm = 0x05,
    Act = 0x06,
    Asp = 0x07,   // attacker skill-difference term -- scales PB + master-strike + dodge together
    Pbs = 0x08,   // perfect-block stat -- SHARED base for perfect block AND master strike. clamp [0,1]
    Cli = 0x09,
    Hlh = 0x0A,
    Slh = 0x0B,
    Sls = 0x0C,
    Dig = 0x0D,
    Exh = 0x0E,
    Psp = 0x0F,
    Lcs = 0x10,
    Srg = 0x11,
    Sco = 0x12,
    Srb = 0x13,
    Sra = 0x14,
    Skp = 0x15,
    Rst = 0x16,
    Pdp = 0x17,
    Eep = 0x18,
    Lpd = 0x19,
    Lpn = 0x1A,
    Ain = 0x1B,
    Hin = 0x1C,
    Fae = 0x1D,
    Dee = 0x1E,
    Osb = 0x1F,
    Dsl = 0x20,   // dodge stat. clamp [0, +inf)
    Cos = 0x21,
    Pac = 0x22,
    Lpb = 0x23,
    Res = 0x24,
    Ors = 0x25,
    Ptp = 0x26,
    None = 0x27,  // "---" not-found sentinel (== count of real ids: 0x00..0x26 = 39)
};

}  // namespace wh::rpgmodule
