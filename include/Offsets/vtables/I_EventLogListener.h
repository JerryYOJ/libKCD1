#pragma once

// -----------------------------------------------
// I_EventLogListener — game-event-log listener interface
// -----------------------------------------------
// Warhorse: wh::framework::I_EventLogListener
// RTTI: .?AVI_EventLogListener@framework@wh@@
//
// PRIMARY (+0x00) base of C_UIEventLog and C_UICombatListener (both global-ns
// UI event systems). wh:: type — NOT interfuscated, slot order == declaration
// order. Modeled in Offsets:: like Offsets::I_LocationListener.
//
// Slot count PROVEN = 1 (no virtual dtor): C_UIEventLog's +0 vtable
// @ 0x1826cf4d0 has exactly one .text slot (qword at 0x1826cf4d8 is the RTTI
// COL of the next vtable). C_UICombatListener's +0 vtable @ 0x1826ccf58 has 2
// slots — slot [1] is a NEW virtual introduced by C_UICombatListener itself.
//
// Listeners register with the event-log manager at S_GameContext+0x58 via
// wh::framework::EventLogRegisterListener_180F00934(mgr, pListener, mask):
//   C_UICombatListener ctor sub_18110CF6C  -> mask 0x01
//   C_UIEventLog InitEventSystem sub_18111C388 -> mask 0xFE
// Unregister: sub_180F01B70 (C_UIEventLog IUIGameEventSystem slot[3]).
//
// The pEvent argument is a polymorphic game event; getters observed in
// C_UIEventLog::OnEvent_18111E3C8: [1]+0x08 GetSender, [2]+0x10 GetType,
// [3]+0x18 GetLevel, [5]+0x28 GetMessage (matches the Sender/Type/Level/
// Message params it forwards to Flash).

namespace Offsets {

struct I_EventLogListener {
    // [0] 0x00 — sole slot. C_UIEventLog: sub_18111E3C8, C_UICombatListener:
    // sub_18110EBF8. Method name "OnEvent" is UNVERIFIED (no string evidence);
    // behavior: receives a logged game event from the S_GameContext+0x58
    // manager.
    virtual void OnEvent(const void* pGameEvent) = 0;
};

}  // namespace Offsets
