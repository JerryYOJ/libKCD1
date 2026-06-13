#pragma once
#include "Offsets/vtables/IFlashUI.h"

#include <cstdint>
#include "Offsets/vtables/I_EventLogListener.h"
#include "Offsets/vtables/IUIGameEventSystem.h"
// (individual UI includes consolidated into IFlashUI.h)

// -----------------------------------------------
// C_UIEventLog 鈥?game-event log -> Flash bridge ("GameEventLog")
// -----------------------------------------------
// RTTI: .?AVC_UIEventLog@@   *** GLOBAL namespace 鈥?declared at global
// scope; file lives in guimodule/ for organization only. ***
// Constructor:     inlined in the factory (no separate ctor function)
// Factory:         sub_18111A9D8  (SAutoRegUIEventSystem<C_UIEventLog>
//                  vtable 0x1822e76d0; allocates 0x30, returns this+8 鈥?the
//                  IUIGameEventSystem subobject CUIManager registers)
// GetName:         sub_1806FE770  -> "UIEventLog"
// InitEventSystem: sub_18111C388  (IUIGameEventSystem slot [2])
// UnloadEventSystem: sub_181120604 (IUIGameEventSystem slot [3]; unregisters
//                  from S_GameContext+0x58 via sub_180F01B70)
// Size:            0x30
//
// Inheritance (RTTI class-hierarchy descriptor):
//   [+0x00] wh::framework::I_EventLogListener  (vtable 0x1826cf4d0, exactly
//           1 slot 鈥?this vtable is the proof the interface has no virtual
//           dtor and one method)
//   [+0x08] IUIGameEventSystem (: IUIPseudoRTTI) (vtable 0x1826cf488, 8 slots)
//
// InitEventSystem (sub_18111C388):
//   1. creates the system->UI IUIEventSystem "GameEventLog" (pFlashUI
//      vtbl+0xC8, direction 1) and registers one event:
//        [0] "OnGameEvent" 鈥?"triggered when GameEvent is fired"
//            Sender  : Int    "Game Event Sender"
//            Type    : Int    "Game Event Type"
//            Level   : Int    "Event level"
//            Message : String "Game event message"
//   2. registers `this` (a1-8) with the game-event-log manager at
//      S_GameContext+0x58 via sub_180F00934(mgr, this, /*mask*/0xFE).
//
// I_EventLogListener::OnEvent (sub_18111E3C8): shows the event only if
// pEvent->GetLevel() (vfunc +0x18) <= ICVar at qword_183785948+0x48
// ->GetIVal(); then forwards GetSender(+0x08)/GetType(+0x10)/GetLevel(+0x18)/
// GetMessage(+0x28) to the sender dispatcher (sub_1811175C8).

// Flash event ids on the "GameEventLog" event system (registration order in
// sub_18111C388).
enum class E_UIEventLogEvent {
    OnGameEvent = 0x00,   // Sender(Int), Type(Int), Level(Int), Message(String)
};

class C_UIEventLog
    : public Offsets::I_EventLogListener        // +0x00  (slot [0] = sub_18111E3C8)
    , public Offsets::IUIGameEventSystem        // +0x08  (: IUIPseudoRTTI)
{
public:
    SUIEventSenderDispatcher<E_UIEventLogEvent>
                             m_eventSender;  // +0x10  (map @0x10, m_pEventSystem @0x20)
    Offsets::IUIEventSystem* m_pUIEvents;    // +0x28  "GameEventLog" system->UI (same object as m_eventSender.m_pEventSystem)

    // Overrides (vtables inherited, not re-declared):
    //   I_EventLogListener::OnEvent          -> sub_18111E3C8
    //   IUIGameEventSystem::GetName          -> sub_1806FE770 ("UIEventLog")
    //   IUIGameEventSystem::InitEventSystem  -> sub_18111C388
    //   IUIGameEventSystem::UnloadEventSystem-> sub_181120604 (slot [3])
};
static_assert(sizeof(C_UIEventLog) == 0x30);
