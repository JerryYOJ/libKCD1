#pragma once

#include "C_CombatSlotTrigger.h"

namespace wh::combatmodule {

// C_CombatTriggerRiposte — master strike window after successful PB.
// vtable @ 0x1821EBB58 (18 slots), dtor: sub_1806AADB4 (frees 0x48)
// Duration from: wh_cs_RiposteSlotDuration
//
// OnActivate:   sets state->m_riposteTriggerActive (+0xC68), fires state+0x6C0
// OnDeactivate: clears m_riposteTriggerActive, fires state+0x6C0
class C_CombatTriggerRiposte : public C_CombatSlotTrigger {
public:
    ~C_CombatTriggerRiposte() override = default;               // [0]  sub_1806AADB4
    const char* GetName() const override { return ""; }          // [3]  sub_1806FC790
    void unk_6() override {}                                     // [6]  sub_180432B18
    void unk_10() override {}                                    // [10] sub_1805CD854
    void unk_11() override {}                                    // [11] sub_1806FAAE0 — returns 0xD
    void OnActivate() override {}                                // [14] RiposteSlotSetup sub_1806EC128
    void OnDeactivate() override {}                              // [15] sub_1806EC190
    void unk_16() override {}                                    // [16] sub_180FAB5F8
};

}  // namespace wh::combatmodule
