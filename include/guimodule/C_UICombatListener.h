#pragma once
#include "Offsets/vtables/IFlashUI.h"

#include <cstdint>
#include "Offsets/vtables/I_EventLogListener.h"
#include "Offsets/vtables/IUIGameEventSystem.h"
// (individual UI includes consolidated into IFlashUI.h)

// -----------------------------------------------
// C_UICombatListener 鈥?combat damage -> Flash bridge ("CombatSensor")
// -----------------------------------------------
// RTTI: .?AVC_UICombatListener@@   *** GLOBAL namespace (no wh::guimodule::
// in the type descriptor) 鈥?declared at global scope; file lives in
// guimodule/ for organization only. ***
// Constructor:     sub_18110CF6C
// Factory:         sub_18110D8AC  (SAutoRegUIEventSystem<C_UICombatListener>
//                  vtable 0x1822e6b38; allocates 0x30, returns this+8 鈥?the
//                  IUIGameEventSystem subobject CUIManager registers)
// GetName:         sub_1806FE680  -> "CombatListener"
// InitEventSystem: sub_18110E460  (IUIGameEventSystem slot [2])
// Size:            0x30
//
// Inheritance (RTTI class-hierarchy descriptor):
//   [+0x00] wh::framework::I_EventLogListener  (vtable 0x1826ccf58, 2 slots:
//           base slot [0] + ONE new virtual introduced by this class)
//   [+0x08] IUIGameEventSystem (: IUIPseudoRTTI) (vtable 0x1826ccf10, 8 slots)
//
// The ctor registers `this` with the game-event-log manager at
// S_GameContext+0x58 via sub_180F00934(mgr, this, /*mask*/1) 鈥?it receives
// only mask-1 (combat/damage) events, complementing C_UIEventLog's 0xFE.
//
// InitEventSystem (sub_18110E460) creates the system->UI IUIEventSystem
// "CombatSensor" (pFlashUI vtbl+0xC8, direction 1) and registers one event:
//   [0] "OnDamage" 鈥?"triggered when an actor recieves an damage"
//       EntityId : Int    "ID of actor entity which recieves the damage"
//       Damage   : Float  "Amount of damage recieved"
//       IsDead   : Bool   "Whether damage was critical."

// Flash event ids on the "CombatSensor" event system (registration order in
// sub_18110E460).
enum class E_UICombatListenerEvent {
    OnDamage = 0x00,   // EntityId(Int), Damage(Float), IsDead(Bool)
};

class C_UICombatListener
    : public Offsets::I_EventLogListener        // +0x00  (slot [0] = sub_18110EBF8)
    , public Offsets::IUIGameEventSystem        // +0x08  (: IUIPseudoRTTI)
{
public:
    // NEW virtual (slot [1] of vtable @ 0x1826ccf58, beyond the 1-slot base):
    // sub_18110F20C 鈥?if pEvent+0x24 == local-player id (S_GameContext+8
    // object, vfunc +0x220, result+0x30), flushes the sender dispatcher via
    // sub_18110B1C0(&m_eventSender). Name/purpose UNVERIFIED beyond that.
    virtual void _vf1(const void* pGameEvent) {}

    SUIEventSenderDispatcher<E_UICombatListenerEvent>
                             m_eventSender;  // +0x10  (map @0x10, m_pEventSystem @0x20)
    Offsets::IUIEventSystem* m_pUIEvents;    // +0x28  "CombatSensor" system->UI (same object as m_eventSender.m_pEventSystem)

    // Overrides (vtables inherited, not re-declared):
    //   I_EventLogListener::OnEvent       -> sub_18110EBF8 (0x459 bytes; builds OnDamage args)
    //   IUIGameEventSystem::GetName       -> sub_1806FE680 ("CombatListener")
    //   IUIGameEventSystem::InitEventSystem -> sub_18110E460
};
static_assert(sizeof(C_UICombatListener) == 0x30);
