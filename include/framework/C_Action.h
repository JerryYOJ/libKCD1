#pragma once

#include <cstdint>
#include "../CryEngine/CryCommon/smartptr.h"
#include "I_Action.h"
#include "I_ActionImpl.h"
#include "C_Signal.h"

namespace wh::framework {

// ---------------------------------------------------------------------------
// C_Action<TPrivate> — concrete action base with MI and data.
//
// RTTI pattern: .?AV?$C_Action@V<TPrivate>@...@@@framework@wh@@
// Primary vtable chain: TPrivate (I_CombatActorActionPrivate or I_CombatActorActionBlock)
// Secondary vtable: I_ActionImpl at +0x10
// Size: 0xD0 bytes (fixed, independent of TPrivate since TPrivate has no data)
//
// Verified instantiations:
//   C_Action<I_CombatActorActionPrivate>  vtable @ 0x1821AAB38, secondary @ 0x1821AAAF0
//   C_Action<I_CombatActorActionBlock>    (Block action only)
// ---------------------------------------------------------------------------
template<typename TPrivate>
class C_Action : public TPrivate, public I_ActionImpl {
public:
    ~C_Action() override = default;

    // ---- Data members ----

    wh::shared::C_Signal<I_Action&, _smart_ptr<I_Action>&>
        m_onActionChanged1;                 // +0x18

    wh::shared::C_Signal<I_Action&, _smart_ptr<I_Action>&>
        m_onActionChanged2;                 // +0x48

    wh::shared::C_Signal<I_Action&>
        m_onActionCompleted;                // +0x78

    bool        m_isStarted;                // +0xA8
    bool        m_isRunning;                // +0xA9
    bool        m_isCompleted;              // +0xAA
    uint8_t     _padAB[5];                  // +0xAB
    void*       m_pActionParams;            // +0xB0
    int32_t     m_priority;                 // +0xB8  (init -1)
    int32_t     m_actionSequenceId;         // +0xBC  (init -1)
    void*       m_pOwnerSubsystem;          // +0xC0
    int32_t     m_contextPriority;          // +0xC8  (init 0)
    uint32_t    _padCC;                     // +0xCC
};

}  // namespace wh::framework
