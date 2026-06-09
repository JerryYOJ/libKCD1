#pragma once

#include <cstdint>
#include <vector>
#include "C_Signal.h"
#include "I_Action.h"
#include "../CryEngine/CryCommon/smartptr.h"

namespace wh::framework {

// Notification kind passed to m_onActionNotification (observed values 0/1/2 in
// sub_18021A1E0 calls: set / removed / replaced). Exact names UNVERIFIED.
enum class E_ActionNotificationType : int32_t;

// ---------------------------------------------------------------------------
// wh::framework::C_ActionDirector — per-slot stack of active actions.
//
// Constructor: sub_180492D08(this, mode). Size: 0xB0.
// Base of combatmodule::C_CombatActorDirector (and other action owners).
//
// Actions are kept in m_actions, indexed by the action's sequence id
// (I_Action::GetActionSequenceId, vtable slot 9 -> action+0xBC). Changing a
// slot fires m_onActionNotification; m_currentSlot/m_currentAction track the
// active slot.
//
// vtable (2 slots):
//   [0] ~C_ActionDirector   (combat override sub_1806014E4)
//   [1] IsActive            (combat override sub_18043423C: owner in combat?)
// ---------------------------------------------------------------------------
class C_ActionDirector {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_ActionDirector;
    virtual ~C_ActionDirector();        // [0]
    virtual bool IsActive() = 0;        // [1]

    wh::shared::C_Signal<E_ActionNotificationType, const int&,
                         const _smart_ptr<I_Action>&, const _smart_ptr<I_Action>&>
        m_onActionNotification;         // +0x08  per-slot add/remove/replace
    wh::shared::C_Signal<const int&, int, int>
        m_onSlotChange;                 // +0x38

    std::vector<_smart_ptr<I_Action>> m_actions;      // +0x68  current action per slot
    std::vector<_smart_ptr<I_Action>> m_actionsPrev;  // +0x80  parallel per-slot vector (purpose UNVERIFIED)

    int32_t  m_mode;                    // +0x98  ctor arg
    int16_t  m_field9C;                 // +0x9C
    uint8_t  _pad9E[2];                 // +0x9E
    int32_t  m_currentSlot;             // +0xA0  -1 = none
    uint32_t _padA4;                    // +0xA4
    _smart_ptr<I_Action> m_currentAction; // +0xA8
};
static_assert(sizeof(C_ActionDirector) == 0xB0, "C_ActionDirector must be 0xB0 bytes");

}  // namespace wh::framework
