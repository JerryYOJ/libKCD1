#pragma once

#include <cstdint>
#include <vector>
#include <map>
#include "C_CombatActorUpdatedObject.h"
#include "../framework/C_Signal.h"

namespace wh::combatmodule {

class I_CombatActor;
struct C_CombatComboData;
enum class E_CombatInputClass : int32_t;
enum class E_CombatZoneId : int32_t;

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
// Methods / wiring (VERIFIED):
//   Ctor: sub_1804F1300 — inits the fields below; wires sub_18045C17C to state+0x30.
//   State-change handler: sub_18045C17C — on event 4/8 writes m_lastComboZone
//     (+0x224) = state+0xC00 (the aimed ZONE); increments m_comboContCounter (+0x21C).
//   TryGetComboAction: sub_180460E54 — gated on state.m_isInCombo && m_comboTriggerActive;
//     walks the +0x200 active-combo vector, matches the fed input-class to the next
//     step, and dispatches g_actionType_comboAttack (step type+zone auto-applied).
// MISATTRIBUTED in earlier analysis (operate on OTHER objects — do NOT trust these):
//   sub_1805CDF80 / sub_1805CDBCC ("ComboSlot*") write floats @+0x1C/+0x20 — not this layout.
//   sub_180F53AF4 / sub_180F5436C — a separate counter-action/sync arbitrator object.
//   sub_1804E2644 — the combat AI auto-attack tick, not the combo manager.
// ---------------------------------------------------------------------------
class C_CombatComboManager : public C_CombatActorUpdatedObject {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_CombatComboManager;
    ~C_CombatComboManager() override = default;
    E_CombatSubsystem GetSubsystemId() const override { return COMBAT_SUB_COMBO_MANAGER; }

    // Force one CLEAN combo-step advance via the engine's own handler (sub_180602C34) --
    // the same routine the state+0x420 ("attack target is opponent") signal invokes on
    // impact, but called directly so it does NOT write state+0xC19 and does NOT emit the
    // +0x420 hit event. Internally: appends the fresh combo seed, then per active combo
    // re-filters candidates (by executed key state+0xBF4 + m_lastComboZone) and
    // ++m_currentStep, compacts, fires the combo-internal m_signal_078. Touches ONLY this
    // manager -- no faked hit, no damage, no impact. No-op unless an active combo with a
    // non-empty eligible seed exists (m_state198 != m_state1A0). Advances only when
    // m_comboFlags(+0x228)==0 (else the engine RESETS the combo instead). Reads the
    // executed key from m_pOwner->m_pState+0xBF4 (written at the attack's OnEnter, so it
    // works even when the swing was perfect-blocked). Caller must throttle to once/step.
    void ForceAdvanceStep();

    // Element of the active-combo tracking vector (m_activeCombos). Field set
    // derived from TryGetComboAction (sub_180460E54) reads — UNVERIFIED beyond
    // the members it touches.
    struct S_ComboCandidate {                       // 0x20
        void*               _unk00;                 // +0x00
        C_CombatComboData*  m_pComboData;           // +0x08
        int32_t             m_stepCount;            // +0x10
        int32_t             m_matchedFlag;          // +0x14  (set to 1 when a step matches)
        void*               _unk18;                 // +0x18
    };
    static_assert(sizeof(S_ComboCandidate) == 0x20);

    struct S_ActiveCombo {                          // 0x28
        void*               _unk00;                 // +0x00
        int32_t             m_currentStep;          // +0x08  (inferred: compared < candidate.m_stepCount)
        int32_t             _unk0C;                 // +0x0C
        std::vector<S_ComboCandidate> m_candidates; // +0x10
    };
    static_assert(sizeof(S_ActiveCombo) == 0x28);

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
    void*           m_transitionBST;        // +0x1B8  BST root node (opaque)
    uint64_t        m_transitionData1C0;    // +0x1C0
    std::vector<void*> m_transitionRules;   // +0x1C8  transition rules (element type UNVERIFIED)
    uint64_t        m_transitionExtra1E0;   // +0x1E0
    uint64_t        m_transitionExtra1E8;   // +0x1E8

    // +0x1F0: combo tracking containers
    std::map<int32_t, void*> m_comboTracker;   // +0x1F0  active-combo map (sub_180208FD8; key/value types UNVERIFIED)
    // +0x200: active-combo tracking vector. Iterated by TryGetComboAction
    // (sub_180460E54); element S_ActiveCombo layout derived from its reads.
    std::vector<S_ActiveCombo> m_activeCombos;  // +0x200
    int32_t         m_comboSeqCounter;      // +0x218  reset/incremented in TryGetComboAction on input-class match
    int32_t         m_comboContCounter;     // +0x21C  incremented in sub_18045C17C (event 8) while in combo
    // +0x220  the combo step's required swing ZONE: TryGetComboAction (sub_180460E54) fires
    // the step's comboAttack ONLY when this == state+0xC00 (the live aimed zone) -- i.e. the
    // player must swing the right DIRECTION; mismatch just marks the step. init -1. This is a
    // ZONE, not an input-class: it is equality-gated against +0xC00, which is the PROVEN aim
    // zone (see S_CombatActorState m_committedAttackZone @+0xC00). [advancement/input-class is handled
    // separately via the step's +0x10 vs CreateAndDispatch a3, NOT this.] (writer not located;
    // type from the gate vs proven-zone +0xC00 + the +0x224 sibling -- producer-trace pending.)
    E_CombatZoneId  m_comboFireGateZone;    // +0x220  (was mislabeled m_comboFireGateInputClass)
    // +0x224  = state+0xC00 (the aimed ZONE) captured on state-change by sub_18045C17C (the
    // m_onStateChange handler does *(this+0x224)=*(state+0xC00)). PROVEN zone (+0xC00 verified
    // = aim zone). The "VERIFIED" only ever meant "== +0xC00", never the semantic type.
    E_CombatZoneId  m_lastComboZone;        // +0x224  (was mislabeled m_lastComboInputClass)
    uint16_t        m_comboFlags;           // +0x228  set 0/1 by TryGetComboAction
    uint8_t         _pad22A[6];             // +0x22A
};
static_assert(sizeof(C_CombatComboManager) == 0x230);

}  // namespace wh::combatmodule
