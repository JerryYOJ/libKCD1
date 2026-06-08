#pragma once

#include <cstdint>
#include "../framework/C_Signal.h"
#include "../CryEngine/CryCommon/smartptr.h"

namespace wh::entitymodule { enum E_HandSlot : int32_t; }

namespace wh::combatmodule {

enum class E_CombatZoneId : int32_t;

class I_CombatActor;
class I_CombatTarget;
class C_CombatActor;
enum class E_CombatActorStateId : int32_t;

// ---------------------------------------------------------------------------
// S_CombatActorState — per-actor combat runtime state.
//
// Allocated: 0xD08 bytes via malloc in sub_1805FDC88
// Initializer: sub_1804F20F8 (signals) + sub_1806A35E4 (state fields)
// Stored at: C_CombatActor+0x4B8
//
// No RTTI, no own vtable — plain struct of C_Signal instances + state data.
// The first 0xBD0 bytes contain 64+ C_Signal<> members (each 0x30 bytes).
// The remaining +0xBD0..+0xD07 is combat runtime state accessed by the
// action system, combo manager, and opponent tracking.
//
// Signal types (from sub_1804F20F8 constructor RTTI vtable writes):
//   C_Signal<I_CombatActor&, bool>
//   C_Signal<I_CombatActor&, E_CombatActorStateId, E_CombatActorStateId>
//   C_Signal<I_CombatActor&, int>  (×8)
//   C_Signal<I_CombatActor&, E_HandSlot>  (×2)
//   C_Signal<I_CombatActor&, float>  (×5)
//   C_Signal<I_CombatActor&, bool>  (×10)
//   C_Signal<I_CombatActor&, S_RestrictedInputClass const&, bool>
//   C_Signal<I_CombatActor&, bool, E_MovementRestrictionScope::Type>
//   C_Signal<I_CombatActor&, bool, E_GuardRequestScope::Type>
//   C_Signal<I_CombatActor&, uint, uint, uint>  (×2)
//   C_Signal<I_CombatActor&>  (×2)
//   C_Signal<I_CombatActor&, I_CombatActor*>
//   C_Signal<I_CombatActor&, I_CombatActor*, I_CombatActor*>
//   C_Signal<I_CombatActor&, I_CombatTarget*, I_CombatTarget*>  (×2)
//   C_Signal<I_CombatActor&, bool, I_CombatActor*>
//   C_Signal<I_CombatActor&, WUID, E_HandSlot>
// ---------------------------------------------------------------------------
struct S_CombatActorState {
    // 63 C_Signal instances. Types verified from sub_1804F20F8 vtable writes.
    // Key connections from C_CombatComboManager ctor (sub_1804F1300) noted inline.

    wh::shared::C_Signal<I_CombatActor&, bool>
        m_onCombatEnter;                                    // +0x000  → sub_1806EBD7C
    wh::shared::C_Signal<I_CombatActor&, E_CombatActorStateId, E_CombatActorStateId>
        m_onStateChange;                                    // +0x030  → sub_18045C17C
    wh::shared::C_Signal<I_CombatActor&, int>
        m_signal_060;                                       // +0x060
    wh::shared::C_Signal<I_CombatActor&, int>
        m_signal_090;                                       // +0x090
    wh::shared::C_Signal<I_CombatActor&, int>
        m_signal_0C0;                                       // +0x0C0
    wh::shared::C_Signal<I_CombatActor&, int>
        m_signal_0F0;                                       // +0x0F0
    wh::shared::C_Signal<I_CombatActor&, int>
        m_signal_120;                                       // +0x120
    wh::shared::C_Signal<I_CombatActor&, int>
        m_signal_150;                                       // +0x150
    wh::shared::C_Signal<I_CombatActor&, int>
        m_signal_180;                                       // +0x180
    wh::shared::C_Signal<I_CombatActor&, wh::entitymodule::E_HandSlot>
        m_signal_1B0;                                       // +0x1B0
    wh::shared::C_Signal<I_CombatActor&, float>
        m_signal_1E0;                                       // +0x1E0
    wh::shared::C_Signal<I_CombatActor&, int>
        m_signal_210;                                       // +0x210
    wh::shared::C_Signal<I_CombatActor&, int>
        m_signal_240;                                       // +0x240
    wh::shared::C_Signal<I_CombatActor&, int>
        m_signal_270;                                       // +0x270
    wh::shared::C_Signal<I_CombatActor&, bool>
        m_signal_2A0;                                       // +0x2A0
    wh::shared::C_Signal<I_CombatActor&, bool>
        m_signal_2D0;                                       // +0x2D0
    wh::shared::C_Signal<I_CombatActor&, bool>
        m_signal_300;                                       // +0x300
    wh::shared::C_Signal<I_CombatActor&, bool>
        m_signal_330;                                       // +0x330  → sub_1806F4984
    wh::shared::C_Signal<I_CombatActor&, bool>
        m_signal_360;                                       // +0x360
    wh::shared::C_Signal<I_CombatActor&, float>
        m_signal_390;                                       // +0x390
    wh::shared::C_Signal<I_CombatActor&, float>
        m_signal_3C0;                                       // +0x3C0
    wh::shared::C_Signal<I_CombatActor&, float>
        m_signal_3F0;                                       // +0x3F0
    wh::shared::C_Signal<I_CombatActor&, bool>
        m_onAttackTargetIsOpponentChanged;                  // +0x420  fired by m_attackTargetIsCurrentOpponent (+0xC19); listener sub_180602C34
    wh::shared::C_Signal<I_CombatActor&, bool>
        m_onOpponentInReachChanged;                         // +0x450  fired by m_isOpponentInReach (+0xC1A)
    wh::shared::C_Signal<I_CombatActor&, bool>
        m_onOpponentInExtendedReachChanged;                 // +0x480  fired by m_isOpponentInExtendedReach (+0xC1B)
    wh::shared::C_Signal<I_CombatActor&, int>
        m_signal_4B0;                                       // +0x4B0
    wh::shared::C_Signal<I_CombatActor&, wh::entitymodule::E_HandSlot>
        m_signal_4E0;                                       // +0x4E0
    wh::shared::C_Signal<I_CombatActor&, bool>
        m_signal_510;                                       // +0x510
    wh::shared::C_Signal<I_CombatActor&, bool>
        m_signal_540;                                       // +0x540
    wh::shared::C_Signal<I_CombatActor&, bool>
        m_signal_570;                                       // +0x570
    wh::shared::C_Signal<I_CombatActor&, I_CombatActor&, bool>
        m_signal_5A0;                                       // +0x5A0
    wh::shared::C_Signal<I_CombatActor&, I_CombatActor&, bool>
        m_signal_5D0;                                       // +0x5D0
    wh::shared::C_Signal<I_CombatActor&, I_CombatActor&, bool>
        m_signal_600;                                       // +0x600
    wh::shared::C_Signal<I_CombatActor&, I_CombatActor&, bool>
        m_signal_630;                                       // +0x630
    wh::shared::C_Signal<I_CombatActor&, I_CombatActor&, bool>
        m_signal_660;                                       // +0x660
    wh::shared::C_Signal<I_CombatActor&, I_CombatActor&, bool>
        m_signal_690;                                       // +0x690
    wh::shared::C_Signal<I_CombatActor&, bool>
        m_onRiposteSlot;                                    // +0x6C0  riposte slot state signal
    wh::shared::C_Signal<I_CombatActor&, bool>
        m_onActionDispatch;                                 // +0x6F0  ACTION DISPATCH TRIGGER → sub_1806ED838
    wh::shared::C_Signal<I_CombatActor&, bool, I_CombatActor*>
        m_signal_720;                                       // +0x720
    wh::shared::C_Signal<I_CombatActor&, uint64_t, wh::entitymodule::E_HandSlot>
        m_signal_750;                                       // +0x750  WUID = uint64_t
    wh::shared::C_Signal<I_CombatActor&, int, wh::entitymodule::E_HandSlot>
        m_onWeaponSlotChange0;                              // +0x780  → sub_1804F6D74
    wh::shared::C_Signal<I_CombatActor&, int, wh::entitymodule::E_HandSlot>
        m_onWeaponSlotChange1;                              // +0x7B0
    wh::shared::C_Signal<I_CombatActor&, bool>
        m_signal_7E0;                                       // +0x7E0
    wh::shared::C_Signal<I_CombatActor&, float>
        m_signal_810;                                       // +0x810
    wh::shared::C_Signal<I_CombatActor&, float>
        m_signal_840;                                       // +0x840
    wh::shared::C_Signal<I_CombatActor&, float>
        m_signal_870;                                       // +0x870
    wh::shared::C_Signal<I_CombatActor&, float>
        m_signal_8A0;                                       // +0x8A0
    wh::shared::C_Signal<I_CombatActor&, float>
        m_signal_8D0;                                       // +0x8D0
    wh::shared::C_Signal<I_CombatActor&, const void*, bool>
        m_onRestrictedInput;                                // +0x900  S_RestrictedInputClass const&
    wh::shared::C_Signal<I_CombatActor&, bool, int>
        m_onMovementRestriction;                            // +0x930  E_MovementRestrictionScope::Type
    wh::shared::C_Signal<I_CombatActor&, bool>
        m_signal_960;                                       // +0x960
    wh::shared::C_Signal<I_CombatActor&, bool>
        m_signal_990;                                       // +0x990
    wh::shared::C_Signal<I_CombatActor&, bool, int>
        m_onGuardRequest;                                   // +0x9C0  E_GuardRequestScope::Type
    wh::shared::C_Signal<I_CombatActor&, bool>
        m_signal_9F0;                                       // +0x9F0
    wh::shared::C_Signal<I_CombatActor&, uint32_t, uint32_t, uint32_t>
        m_signal_A20;                                       // +0xA20
    wh::shared::C_Signal<I_CombatActor&, uint32_t, uint32_t, uint32_t>
        m_signal_A50;                                       // +0xA50
    wh::shared::C_Signal<I_CombatActor&>
        m_signal_A80;                                       // +0xA80
    wh::shared::C_Signal<I_CombatActor&>
        m_signal_AB0;                                       // +0xAB0
    wh::shared::C_Signal<I_CombatActor&, I_CombatActor*>
        m_signal_AE0;                                       // +0xAE0
    wh::shared::C_Signal<I_CombatActor&, I_CombatActor*, I_CombatActor*>
        m_onOpponentChange;                                 // +0xB10  → sub_1804F6D74
    wh::shared::C_Signal<I_CombatActor&, I_CombatTarget*, I_CombatTarget*>
        m_onTargetChange0;                                  // +0xB40
    wh::shared::C_Signal<I_CombatActor&, I_CombatTarget*, I_CombatTarget*>
        m_onTargetChange1;                                  // +0xB70
    wh::shared::C_Signal<I_CombatActor&, bool>
        m_signal_BA0;                                       // +0xBA0  (last signal)

    // ---- Post-signal combat runtime state ----

    C_CombatActor*  m_pOwner;               // +0xBD0  back-pointer to owning actor
    bool            m_isInCombat;           // +0xBD8  combat engagement flag
    uint8_t         _padBD9[3];             // +0xBD9
    int32_t         m_combatMode;           // +0xBDC  combat mode ID
    int32_t         m_combatStateCategory;  // +0xBE0  state category (compared against dword_18359BEA0 in sub_1804605D0)
    int32_t         m_guardTypeId;          // +0xBE4  current guard type
    E_CombatZoneId  m_attackZoneId;         // +0xBE8  current attack zone
    int32_t         m_actionTypeId;         // +0xBEC  live current action type id (set on action init, signal @ +0xF0)
    int32_t         m_weaponClassId;        // +0xBF0  weapon class
    uint32_t        _padBF4;                // +0xBF4
    int32_t         m_weaponGroupId;        // +0xBF8  weapon group
    E_CombatZoneId  m_defenseZoneId;        // +0xBFC  VERIFIED: used as zone param for PB/block dispatch
    int32_t         m_inputClassId;         // +0xC00  input class
    uint8_t         _padC04[0x10];          // +0xC04

    bool            m_isBlocking;           // +0xC14
    bool            m_isAttacking;          // +0xC15
    uint8_t         _padC16;                // +0xC16
    bool            m_isInCombo;            // +0xC17
    uint8_t         _padC18;                // +0xC18
    bool            m_attackTargetIsCurrentOpponent; // +0xC19  edge flag: action target == m_pOpponent
    bool            m_isOpponentInReach;    // +0xC1A  opponent in angle cone + weapon reach
    bool            m_isOpponentInExtendedReach; // +0xC1B  reach + margin (looser band)
    uint32_t        m_attackersInReachCount; // +0xC1C  # attackers with this actor in extended reach
    int32_t         m_riposteState;         // +0xC20  (unverified)
    uint8_t         _padC24[0x10];          // +0xC24

    bool            m_isPerfectBlocking;    // +0xC34
    bool            m_isDodging;            // +0xC35
    uint8_t         _padC36[2];             // +0xC36
    uint32_t        m_dodgeState;           // +0xC38
    bool            m_isInPerfectBlockAction; // +0xC3C  set by PB action OnInitialize (distinct from +0xC34)
    uint8_t         _padC3D[3];             // +0xC3D  (no hunt-attack bool exists)

    uint64_t        m_activeActionPtr;      // +0xC40  current action (_smart_ptr)
    uint64_t        m_pendingActionPtr;     // +0xC48  pending action
    int32_t         m_transitionData;       // +0xC50
    int32_t         m_pbTriggerCount;       // +0xC54  active PB triggers (>0 = PB window open)
    int32_t         m_syncDodgeTriggerCount; // +0xC58  active SyncDodge triggers (>0 = dodge window open)
    int32_t         m_syncRiposteTriggerCount; // +0xC5C  active SyncRiposte triggers (>0 = riposte window open)
    uint64_t        m_unknown_C60;          // +0xC60
    bool            m_riposteTriggerActive; // +0xC68  C_CombatTriggerRiposte flag (true = riposte window open)
    bool            m_comboTriggerActive;   // +0xC69  C_CombatTriggerCombo flag (true = combo slot open)
    uint8_t         _padC6A[0x2E];          // +0xC6A

    I_CombatTarget* m_pPrevTarget;          // +0xC98  previous target (compared by opponent manager)
    I_CombatTarget* m_pCurrentTarget;       // +0xCA0  current target (compared by opponent manager)
    C_CombatActor*  m_pOpponent;            // +0xCA8  active 1v1 opponent (read by sub_1804605D0)
    uint8_t         _padCB0[8];             // +0xCB0

    uint64_t        m_unknown_CB8;          // +0xCB8
    uint64_t        m_unknown_CC0;          // +0xCC0
    uint8_t         _padCC8[0x18];          // +0xCC8

    uint64_t        m_unknown_CE0;          // +0xCE0
    uint64_t        m_unknown_CE8;          // +0xCE8
    int32_t         m_unknown_CF0;          // +0xCF0
    int16_t         m_unknown_CF4;          // +0xCF4
    bool            m_unknown_CF6;          // +0xCF6
    bool            m_unknown_CF7;          // +0xCF7
    int32_t         m_unknown_CF8;          // +0xCF8
    int32_t         m_combatFlags;          // +0xCFC
    int32_t         m_unknown_D00;          // +0xD00
    int32_t         _padD04;                // +0xD04
};
static_assert(sizeof(S_CombatActorState) == 0xD08, "S_CombatActorState must be 0xD08 bytes");

}  // namespace wh::combatmodule
