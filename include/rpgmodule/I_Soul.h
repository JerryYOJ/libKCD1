#pragma once

#include <cstdint>
#include "E_DerivedStat.h"

// -----------------------------------------------
// I_Soul -- Soul interface (pure virtual)
// -----------------------------------------------
// RTTI: .?AVI_Soul@rpgmodule@wh@@
// vtable: 0x182228260 (C_Soul implementation)
// 64+ virtual methods — large interface spanning stats, skills, perks, buffs, combat
//
// Key vtable slots (byte offset / 8 = index):
//   [0]  = destructor
//   [9]  = sub_18056C29C — returns derived_stat(0x37) == 0.0 (bool predicate)
//   [10] = sub_180569EA4 — returns derived_stat(0x5A) > 0.0 (bool predicate)
//   [20] = sub_180631F20 — reads *(*(soul+0xBC8)+0x14) (archetype value, same path as GetGender)
//   [26] = sub_18064D750 — GetFactionIDInternal (walks parent chain via soul+0x480, reads root+0x294)
//   [33] = sub_1804A67C0 — reads *(uint32*)(soul+0x3C0)
//   [38] = sub_18027B7B4 — builds array from soul+0x2F0 range (complex)
//   [43] = sub_180284170 — entity/faction lookup
//   [44] = sub_180229E1C — SetState
//   [45] = sub_180229E78 — returns RPG param by index (0→param[0x99], 2→param[0xD6], etc.)
//   [47] = sub_180229880 — GetModifiedStatValue (walks buff list, applies modifiers, clamps)
//   [48] = sub_180339650 — GetDerivedStat (simple path)
//   [49] = sub_180339980 — GetDerivedStatFull (big switch, ~100 stat IDs)
//   [59] = offset 0x1D8 — returns C_PerkList* (used by UI perk iteration)

namespace wh::rpgmodule {

class C_PerkList;

class I_Soul {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_I_Soul;
    virtual ~I_Soul() = default;                     // [0]  0x1806f8b20
    virtual void vf01() {}                            // [1]  0x1811f6168
    virtual void vf02() {}                            // [2]  0x1806ff680
    virtual void vf03() {}                            // [3]  0x1806f94a0
    virtual void vf04() {}                            // [4]  0x1811f83ec
    virtual void vf05() {}                            // [5]  0x180229f70
    virtual void vf06() {}                            // [6]  0x180228950
    virtual void vf07() {}                            // [7]  0x1811f8238
    virtual void vf08() {}                            // [8]  0x1811f8270
    virtual bool IsStatAtZero() { return false; }     // [9]  0x18056c29c — derived_stat(0x37)==0.0
    virtual bool HasCapability() { return false; }    // [10] 0x180569ea4 — derived_stat(0x5A)>0.0
    virtual void vf11() {}                            // [11] 0x180209ac0
    virtual void vf12() {}                            // [12] 0x1811f6b38
    virtual void vf13() {}                            // [13] 0x1811f833c
    virtual void vf14() {}                            // [14] 0x1811f832c
    virtual void vf15() {}                            // [15] 0x180595808
    virtual void vf16() {}                            // [16] 0x180595820
    virtual void vf17() {}                            // [17] 0x1806ff660
    virtual void vf18() {}                            // [18] 0x1806ff640
    virtual void vf19() {}                            // [19] 0x1803bb250
    virtual uint32_t GetArchetypeField14() { return 0; } // [20] 0x180631f20 — reads *(*(soul+0xBC8)+0x14)
    virtual void vf21() {}                            // [21] 0x18064fb88
    virtual void vf22() {}                            // [22] 0x18064d770
    virtual void vf23() {}                            // [23] 0x180310c20
    virtual void vf24() {}                            // [24] 0x1802287d0
    virtual void vf25() {}                            // [25] 0x1802287b4
    virtual uint32_t GetFactionIDInternal() { return 0; } // [26] 0x18064d750 — walks parent chain, reads root+0x294
    virtual void vf27() {}                            // [27] 0x1802281e4
    virtual void vf28() {}                            // [28] 0x1806925dc
    virtual void vf29() {}                            // [29] 0x1811f608c
    virtual void vf30() {}                            // [30] 0x1806ff690
    virtual void vf31() {}                            // [31] 0x1806ff690  (same as [30])
    virtual void vf32() {}                            // [32] 0x1806ff6a0
    virtual uint32_t GetBuffStateFlags() { return 0; } // [33] 0x1804a67c0 — reads *(uint32*)(soul+0x3C0)
    virtual void vf34() {}                            // [34] 0x1806ff810
    virtual void vf35() {}                            // [35] 0x1806ff6b0
    virtual void vf36() {}                            // [36] 0x1805b0560
    virtual void vf37() {}                            // [37] 0x1805b0570
    virtual void GetSoulDataArray(void* out) {}       // [38] 0x18027b7b4 — builds array from soul+0x2F0
    virtual void vf39() {}                            // [39] 0x1806f8b90
    virtual void vf40() {}                            // [40] 0x1806ff820
    virtual void vf41() {}                            // [41] 0x1806fc8c0
    virtual void vf42() {}                            // [42] 0x1806837e4
    virtual void vf43() {}                            // [43] 0x180284170
    virtual void SetState(int state) {}               // [44] 0x180229e1c
    virtual float GetRpgParamByState(int state) { return 0.0f; } // [45] 0x180229e78 — returns rpg_params by state index
    virtual void vf46() {}                            // [46] 0x180284368
    virtual float GetModifiedStatValue(int id) { return 0.0f; } // [47] 0x180229880 — walks buff list, applies modifiers
    virtual float GetDerivedStat(E_DerivedStat index) { return 0.0f; } // [48] 0x180339650 — simple derived stat
    virtual float GetDerivedStatFull(E_DerivedStat index) { return 0.0f; } // [49] 0x180339980 — full computation (big switch over E_DerivedStat)
    virtual void vf50() {}                            // [50] 0x1811f60ac
    virtual void vf51() {}                            // [51] 0x1811f6b5c
    virtual void vf52() {}                            // [52] 0x180228a54
    virtual void vf53() {}                            // [53] 0x18023b6bc
    virtual void vf54() {}                            // [54] 0x1811f55e8
    virtual void vf55() {}                            // [55] 0x1802113b0
    virtual void vf56() {}                            // [56] 0x1806578a0
    virtual void vf57() {}                            // [57] 0x180228930
    virtual void vf58() {}                            // [58] 0x1806e5750
    virtual C_PerkList* GetActivePerkList() { return nullptr; } // [59] 0x1806ff460 — 0x1D8/8, used by UI perk iteration
    virtual void vf60() {}                            // [60] 0x180664d48
    virtual void vf61() {}                            // [61] 0x180208c04
    virtual void vf62() {}                            // [62] 0x1806ff650
    virtual void vf63() {}                            // [63] 0x1806ff650  (same as [62])
};

}  // namespace wh::rpgmodule
