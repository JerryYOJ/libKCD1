#pragma once

#include <cstdint>
#include "C_CombatActorUpdatedObject.h"
#include "../framework/C_Signal.h"

namespace wh::combatmodule {

class I_CombatActor;

// ---------------------------------------------------------------------------
// C_CombatComboManager — manages combo state, transition table, and slots.
//
// RTTI: .?AVC_CombatComboManager@combatmodule@wh@@
// Constructor: sub_1804F1300
// Subsystem ID: COMBAT_SUB_COMBO_MANAGER (0x10)
// Stored at: C_CombatActor+0x728
// Size: 0x230 bytes
//
// Inherits: C_CombatActorUpdatedObject : C_CombatActorObject
//
// Owns:
//   - 7 C_Signal instances for combo events (+0x18..0x168)
//   - Transition rule table at +0x1B0 (Guard→Attack, Guard→Block, etc.)
//   - Combo state tracking
//
// Connected to S_CombatActorState signals (in ctor):
//   state+0x000 → sub_1806EBD7C (on combat enter)
//   state+0x030 → sub_18045C17C (on state change)
//   state+0x330 → sub_1806F4984
//   state+0x420 → sub_180602C34
//   state+0x6F0 → sub_1806ED838 (ACTION DISPATCH trigger)
//   state+0x780 → sub_1804F6D74 (weapon change)
//   state+0xB10 → sub_1804F6D74 (opponent change)
//   actor+0x168 → sub_1806F6F08
//
// Key methods:
//   Reset: sub_180F53AF4
//   GetDebugInfo: sub_180F5436C
//   OnTargetChange: sub_1805D9DB8
//   UpdateOpponent: sub_180303720
//   OnActionSignal: sub_1804E2644
//   ComboSlotSetup: sub_1805CDF80
//   ComboSlotEventHandler: sub_18045C0D4
//   ComboSlotUpdate: sub_1805CDBCC
//   RiposteSlotSetup: sub_1806EC128
// ---------------------------------------------------------------------------
class C_CombatComboManager : public C_CombatActorUpdatedObject {
public:
    ~C_CombatComboManager() override = default;
    E_CombatSubsystem GetSubsystemId() const override { return COMBAT_SUB_COMBO_MANAGER; }

    // +0x18..0x168: 7 C_Signal instances (each 0x30 bytes = 0xD8 total)
    wh::shared::C_Signal<I_CombatActor&, bool>
        m_onComboSlotChanged;                               // +0x018
    wh::shared::C_Signal<I_CombatActor&, int, bool>
        m_onComboStepChanged;                               // +0x048
    wh::shared::C_Signal<I_CombatActor&>
        m_signal_078;                                       // +0x078
    wh::shared::C_Signal<I_CombatActor&>
        m_signal_0A8;                                       // +0x0A8
    wh::shared::C_Signal<I_CombatActor&, int>
        m_signal_0D8;                                       // +0x0D8
    wh::shared::C_Signal<I_CombatActor&, int>
        m_signal_108;                                       // +0x108
    wh::shared::C_Signal<I_CombatActor&, int>
        m_signal_138;                                       // +0x138

    // +0x168: post-signal state data
    uint64_t        m_comboData168;     // +0x168
    uint8_t         _pad170[0x28];      // +0x170

    // +0x198..0x1AF: combo state
    uint64_t        m_state198;         // +0x198
    uint64_t        m_state1A0;         // +0x1A0
    uint64_t        m_state1A8;         // +0x1A8

    // +0x1B0: Transition rule table (sub_1806024EC)
    // Maps current action → valid next actions.
    // Contains: float timeScale, BST root, vector of rules, counters.
    float           m_transitionTimeScale;  // +0x1B0  (init 1.0f)
    uint32_t        _pad1B4;                // +0x1B4
    uint64_t        m_transitionBST;        // +0x1B8  BST root node
    uint64_t        m_transitionData1C0;    // +0x1C0
    uint64_t        m_transitionVecBegin;   // +0x1C8  transition vector begin
    uint64_t        m_transitionVecEnd;     // +0x1D0
    uint64_t        m_transitionVecCap;     // +0x1D8
    uint64_t        m_transitionExtra1E0;   // +0x1E0
    uint64_t        m_transitionExtra1E8;   // +0x1E8

    // +0x1F0: additional state
    void*           m_pComboTracker;        // +0x1F0  (sub_180208FD8 return, tracks active combo)
    uint64_t        m_unknown1F8;           // +0x1F8
    uint64_t        m_unknown200;           // +0x200
    uint64_t        m_unknown208;           // +0x208
    uint64_t        m_unknown210;           // +0x210
    uint64_t        m_unknown218;           // +0x218
    int32_t         m_comboId;              // +0x220  (init -1)
    int32_t         m_comboStepId;          // +0x224  (init -1)
    uint16_t        m_comboFlags;           // +0x228  (init 0)
    uint8_t         _pad22A[6];             // +0x22A
};
static_assert(sizeof(C_CombatComboManager) == 0x230);

}  // namespace wh::combatmodule
