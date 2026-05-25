#pragma once

#include <cstdint>
#include "C_CombatTrigger.h"

namespace wh::combatmodule {

// ---------------------------------------------------------------------------
// C_CombatSlotTrigger — trigger with timing slot state.
//
// RTTI: .?AVC_CombatSlotTrigger@combatmodule@wh@@
// Destructor: sub_18056B2CC (releases ref-counted ptr at +0x40)
// Size: 0x48 bytes
//
// Adds 6 virtual methods [12]-[17] to C_CombatTrigger's 12.
// Combo and Riposte triggers have 18 total slots.
// PerfectBlock adds 5 more ([18]-[22]) for 23 total.
//
// Shared vtable slots [12]-[17] (same index across Combo/Riposte/PB):
//   [12] unk_12 — setup/evaluate (PB: ComboSlotUpdate, Combo/Riposte: sub_1806A4188)
//   [13] unk_13 — returns int (all: sub_1806F8140 returns 1)
//   [14] OnActivate — fires when trigger activates (PB: sub_1805FB374, Combo: sub_1806D34D0, Riposte: sub_1806EC128)
//   [15] OnDeactivate — fires when trigger deactivates (PB: sub_1805FB308, Combo: sub_1806D34E4, Riposte: sub_1806EC190)
//   [16] unk_16 — (PB: sub_180FAB598, Combo/Riposte: nop)
//   [17] unk_17 — (all: nop)
// ---------------------------------------------------------------------------
class C_CombatSlotTrigger : public C_CombatTrigger {
public:
    ~C_CombatSlotTrigger() override = default;
    virtual void unk_12() {}                        // [12] setup/evaluate
    virtual int  unk_13() { return 1; }             // [13] sub_1806F8140
    virtual void OnActivate() {}                    // [14] fires on trigger activation
    virtual void OnDeactivate() {}                  // [15] fires on trigger deactivation
    virtual void unk_16() {}                        // [16]
    virtual void unk_17() {}                        // [17]

    uint16_t    m_slotState;        // +0x18
    uint8_t     _pad1A;             // +0x1A
    bool        m_isActive;         // +0x1B  slot open flag
    float       m_duration;         // +0x1C  timing window duration
    float       m_scaleFactor;      // +0x20  blend factor
    uint32_t    _pad24;             // +0x24
    uint64_t    m_timerData[3];     // +0x28  timer (0x18 bytes)
    void*       m_pRefCounted;      // +0x40  ref-counted object
};
static_assert(sizeof(C_CombatSlotTrigger) == 0x48);

}  // namespace wh::combatmodule
