#pragma once

#include <cstdint>

// ===========================================================================
// wh::rpgmodule::E_DerivedStat
// ===========================================================================
// The `index` argument of C_Soul::GetDerivedStat / GetDerivedStatFull
// (I_Soul vtable slots 48/49 = sub_180339650 / sub_180339980). It is dispatched
// by a ~110-case switch in sub_180339980.
//
// There is NO `derived_stat` game table in the paks. The authoritative id<->code
// map is a BINARY registry built by the rpgmodule global ctor sub_180128740: a
// 16-byte-stride table at .data 0x1835ABB00..0x1835AC1E0 of {const char* code; int id}.
// The enumerator names below are those verbatim 3-letter codes (binary-VERIFIED
// from the .rdata string literals) — the same codes Lua and the Flash UI use as
// string keys, e.g. player.soul:GetDerivedStat("mst").
//   code -> id converter : C_RPGUtils vtable slot 11 (sub_1802ADE84), returns 0x6E
//                          ("---" / None) when a code is not found.
//   Lua scriptbind       : GetDerivedStat handler sub_1811AF7E0 (reg sub_1811CCC44).
//
// Semantic meanings in the comments are cross-referenced from the Flash enums
// (inventoryEnums.as) and Scripts/Quests + Scripts/FeatureTests; only ~17 are
// pinned that way, the rest are the raw codes [meaning UNVERIFIED].
//
// [cached]  = base value is stored in S_SoulDerivedStatCache (C_Soul+0xA94),
//             recomputed by sub_180549518. (ids 0,3,5,0x19,0x1A,0x1D,0x25,0x26,
//             0x48,0x55,0x62,0x63.)
// Engine note: sub_180339980 returns a real computed base only for the cached/
// computed/param/field-read/flag-test ids; a number of ids return a flat 1.0f or
// 0.0f from the switch and get their real value from the buff/perk path
// (sub_1803385BC) instead — so a 0.0f here does NOT mean the stat is unused
// (e.g. 0x13 hac, 0x3F dru, 0x6D deb are real, RTTI-confirmed stats).
// ===========================================================================

namespace wh::rpgmodule {

enum class E_DerivedStat : int32_t {
    Cha = 0x00,   // charisma                         [cached]
    Rch = 0x01,
    Vib = 0x02,
    Evi = 0x03,   // visibility (how visible you are) [cached]
    Lpv = 0x04,
    Con = 0x05,   // conspicuousness                  [cached]
    Mst = 0x06,   // stamina (current)
    Mhs = 0x07,   // max stamina
    Hlt = 0x08,   // health
    Sdt = 0x09,
    Src = 0x0A,
    Fov = 0x0B,
    Vir = 0x0C,
    Tsr = 0x0D,   // sense
    Dtf = 0x0E,
    Dbf = 0x0F,
    Pt1 = 0x10,
    Pt5 = 0x11,
    Dai = 0x12,
    Hac = 0x13,   // haggle / "second chances" (negotiation)
    Lsa = 0x14,
    Lfu = 0x15,
    Lio = 0x16,
    Cap = 0x17,   // carry capacity (max weight)
    Alo = 0x18,
    Oad = 0x19,   //                                  [cached]
    Owa = 0x1A,   //                                  [cached]
    Wud = 0x1B,
    Lvl = 0x1C,   // level (switch special-cases fractional level)
    Noi = 0x1D,   // noise                            [cached]
    Fsm = 0x1E,
    Nrs = 0x1F,   // movement speed
    Rsa = 0x20,
    Ble = 0x21,   // bleeding
    Ibi = 0x22,
    Bow = 0x23,
    Cow = 0x24,
    Aco = 0x25,   //                                  [cached]
    Caw = 0x26,   // carry weight (current load)      [cached]
    Rcw = 0x27,
    Mor = 0x28,   // morality
    Dem = 0x29,
    Mcf = 0x2A,
    Obe = 0x2B,   // obedience
    Psr = 0x2C,
    Xpm = 0x2D,   // xp multiplier (field-read)
    Osl = 0x2E,
    Mos = 0x2F,
    Ore = 0x30,
    Caf = 0x31,
    Rdq = 0x32,   // (param-lookup)
    Erq = 0x33,
    Sle = 0x34,
    Coc = 0x35,
    Ufo = 0x36,
    Mut = 0x37,
    Prb = 0x38,
    Fpa = 0x39,
    Apa = 0x3A,
    Cag = 0x3B,
    Def = 0x3C,
    Fol = 0x3D,
    Bad = 0x3E,
    Dru = 0x3F,   // (RTTI-confirmed real stat; base from buff/perk path)
    Poi = 0x40,
    Pos = 0x41,
    Ran = 0x42,
    Iex = 0x43,
    Hcm = 0x44,
    Was = 0x45,
    Grm = 0x46,
    Brm = 0x47,
    Drt = 0x48,   //                                  [cached]
    Hko = 0x49,   // (param-lookup)
    Enc = 0x4A,
    Fdm = 0x4B,
    Sma = 0x4C,
    Bma = 0x4D,
    Hgs = 0x4E,
    Pds = 0x4F,   // (param-lookup)
    Sha = 0x50,
    Pbm = 0x51,
    Rml = 0x52,
    Hml = 0x53,   // (param-lookup)
    Bso = 0x54,
    Bld = 0x55,   //                                  [cached]
    Bba = 0x56,   // (field-read)
    Arr = 0x57,   // (RTTI-confirmed real stat)
    Jrm = 0x58,
    Sur = 0x59,
    Imm = 0x5A,   // (flag-test, Soul+0x284)
    Apr = 0x5B,   // (flag-test, Soul+0x284)
    Ppr = 0x5C,   // (flag-test, Soul+0x284)
    Upr = 0x5D,   // (flag-test, Soul+0x284)
    Cds = 0x5E,
    Edm = 0x5F,
    Prc = 0x60,
    Cdw = 0x61,
    Eqw = 0x62,   // equipped weight                  [cached]
    Pla = 0x63,   //                                  [cached]
    Wbc = 0x64,
    Cbi = 0x65,
    Nbi = 0x66,
    Alc = 0x67,
    Map = 0x68,
    Adm = 0x69,
    Btw = 0x6A,
    Owl = 0x6B,
    Rms = 0x6C,
    Deb = 0x6D,   // (RTTI-confirmed real stat; base from buff/perk path)

    None = 0x6E,  // "---" sentinel: returned by the code->id converter (sub_1802ADE84)
                  // when a code is not found. Also == the count of real ids (0x00..0x6D = 110).
};

}  // namespace wh::rpgmodule
