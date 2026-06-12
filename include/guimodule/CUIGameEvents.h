#pragma once

#include <cstdint>
#include <map>
#include "Offsets/vtables/IUIEventSystem.h"
#include "Offsets/vtables/IGameFramework.h"
#include "guimodule/SUIEventReceiverDispatcher.h"

// -----------------------------------------------
// CUIGameEvents — game-flow flash events ("Game" event system)
// -----------------------------------------------
// RTTI: .?AVCUIGameEvents@guimodule@wh@@  (single vtable @ 0x1822e76e8, no
// bases — its own polymorphic root, 3 slots; see virtuals below)
// Constructor: sub_1811193B8 (called by CUIManager ctor sub_181125C08,
//              allocation 0x60); the ctor itself calls InitEventSystem
//              (sub_18111C0AC) at the end
// Destructor:  slot [2] sub_18111A2C8 (body sub_181119DA0) — CUIManager dtor
//              sub_18112906C deletes this member through vtbl+0x10, unlike the
//              IUIModule-based siblings (slot [0])
// Size:        0x60
//
// Derived from CryEngine GameSDK Game/UI/UIGameEvents.{h,cpp} (CUIGameEvents);
// the Warhorse version dropped the IUIGameEventSystem/IUIModule bases — it is
// a direct member of CUIManager (+0x28).
//
// InitEventSystem (sub_18111C0AC):
//  - m_pGameFramework = gEnv.pGame->vtbl+0x78 (GetIGameFramework)
//  - m_pLevelSystem   = framework->GetILevelSystem (IGameFramework [24] +0xC0)
//  - m_pUIFunctions = pFlashUI->CreateEventSystem("Game", eEST_SYSTEM_TO_UI);
//    sender event "OnExitGame" ("Triggered by flowgraph function 'ExitGame'.")
//    -> m_eventSenderMap[OnExitGame=0]
//  - m_pUIEvents = pFlashUI->CreateEventSystem("Game", eEST_UI_TO_SYSTEM);
//    m_eventDispatcher.Init(m_pUIEvents, this, "CUIGameEvents"); receiver
//    events (registration helpers sub_181116D00/sub_181116A64):
//      "PauseGame"  (FadeOut: "Fade out time in ms.")  -> handler embedded in desc (sub_181116D00)
//      "ResumeGame"                                    -> sub_18111E670
//      "ExitGame"                                      -> sub_18111E2F4
//      "StartGame" ("sends the GAMEPLAY START event")  -> sub_18111E690

namespace wh::guimodule {

// Sender events on the "Game" eEST_SYSTEM_TO_UI event system.
enum class E_UIGameEvent {
    OnExitGame = 0,
};

class CUIGameEvents {
public:
    virtual void InitEventSystem() {}   // [0] 0x00  sub_18111C0AC (also called directly by the ctor)
    virtual void _vf1() {}              // [1] 0x08  nop (UNVERIFIED purpose)
    virtual ~CUIGameEvents() = default; // [2] 0x10  sub_18111A2C8

    Offsets::IUIEventSystem*  m_pUIEvents;     // +0x08  "Game" eEST_UI_TO_SYSTEM (listener "CUIGameEvents")
    Offsets::IUIEventSystem*  m_pUIFunctions;  // +0x10  "Game" eEST_SYSTEM_TO_UI

    // EMBEDDED dispatcher (0x28: vtbl 0x1822e7560, mFunctionMap @+0x20,
    // m_pEventSystem @+0x30 = m_pUIEvents, m_pThis @+0x38 — set by Init).
    SUIEventReceiverDispatcher<CUIGameEvents> m_eventDispatcher; // +0x18 .. 0x40

    Offsets::IGameFramework*  m_pGameFramework; // +0x40
    void*                     m_pLevelSystem;   // +0x48  CLevelSystem* (IGameFramework::GetILevelSystem)

    std::map<E_UIGameEvent, unsigned int> m_eventSenderMap; // +0x50
};
static_assert(sizeof(CUIGameEvents) == 0x60);

}  // namespace wh::guimodule
