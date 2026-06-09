#pragma once

#include "C_CombatSlotTrigger.h"

namespace wh::combatmodule {

// C_CombatTriggerPerfectBlock — perfect block timing window.
// vtable @ 0x1821BF238 (23 slots — 5 more than Combo/Riposte)
// dtor: sub_1806EA874 (frees 0x48)
// Created by Mannequin "PerfectBlockSlot" animation event (sub_1805CD1A8)
//
// OnActivate (sub_1805FB374): increments state->m_pbTriggerCount (+0xC54),
//   fires signal state+0x5D0 on 0→1
// OnDeactivate (sub_1805FB308): decrements m_pbTriggerCount,
//   fires signal state+0x5D0 on 1→0
class C_CombatTriggerPerfectBlock : public C_CombatSlotTrigger {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_CombatTriggerPerfectBlock;
    ~C_CombatTriggerPerfectBlock() override = default;          // [0]  sub_1806EA874
    const char* GetName() const override { return ""; }         // [3]  sub_1806FC780
    void unk_6() override {}                                    // [6]  sub_18043244C
    void unk_10() override {}                                   // [10] sub_1805CD854
    void unk_11() override {}                                   // [11] sub_1806F8C40 — returns 0xD
    void unk_12() override {}                                   // [12] ComboSlotUpdate sub_1805CDBCC
    void OnActivate() override {}                               // [14] sub_1805FB374 (pbTriggerCount++)
    void OnDeactivate() override {}                             // [15] sub_1805FB308 (pbTriggerCount--)
    void unk_16() override {}                                   // [16] sub_180FAB598

    // PB-only methods [18]-[22] (not present on Combo/Riposte):
    virtual void unk_18() {}                                    // [18] sub_180432D48
    virtual void unk_19() {}                                    // [19] sub_1803953E0
    virtual void unk_20() {}                                    // [20] sub_1806F53C0
    virtual void unk_21() {}                                    // [21] sub_1805CDF4C
    virtual void unk_22() {}                                    // [22] sub_1805CDF0C
};

}  // namespace wh::combatmodule
