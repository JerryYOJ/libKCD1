#pragma once

#include "C_CombatSlotTrigger.h"

namespace wh::combatmodule {

// C_CombatTriggerCombo — combo follow-up window.
// vtable @ 0x1821EBBF0 (18 slots), dtor: sub_1806AAD80 (frees 0x48)
//
// OnActivate:   sets state->m_comboTriggerActive (+0xC69), fires state+0x6F0
// OnDeactivate: clears m_comboTriggerActive, fires state+0x6F0
class C_CombatTriggerCombo : public C_CombatSlotTrigger {
public:
    ~C_CombatTriggerCombo() override = default;                 // [0]  sub_1806AAD80
    const char* GetName() const override { return ""; }         // [3]  sub_1806FC760
    void unk_6() override {}                                    // [6]  sub_180432AEC
    void unk_10() override {}                                   // [10] sub_1805CD854
    void unk_11() override {}                                   // [11] sub_1803953E0
    void OnActivate() override {}                               // [14] sub_1806D34D0
    void OnDeactivate() override {}                             // [15] sub_1806D34E4
};

}  // namespace wh::combatmodule
