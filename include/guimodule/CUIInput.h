#pragma once

#include <cstdint>
#include <map>
#include "Offsets/vtables/IActionListener.h"
#include "Offsets/vtables/IVirtualKeyboardEvents.h"
#include "Offsets/vtables/IHardwareMouseEventListener.h"
#include "Offsets/vtables/IUIEventSystem.h"
#include "guimodule/SUIEventReceiverDispatcher.h"

// CryAction/IActionMapManager.h — TActionHandler<T>
// (std::multimap<ActionId, bool (T::*)(EntityId, const ActionId&, int, float)>)
template<typename T> class TActionHandler;

// -----------------------------------------------
// CUIInput — UI input routing (action map / virtual keyboard / hardware mouse)
// -----------------------------------------------
// RTTI: .?AVCUIInput@guimodule@wh@@  (3 vtables: +0x00 / +0x08 / +0x10)
//   0x1822e8ac8 IActionListener            [0] dtor sub_181129B2C
//                                          [1] OnAction sub_180200140
//                                          [2] AfterAction nop
//   0x1822e8ae8 IVirtualKeyboardEvents     (see IVirtualKeyboardEvents.h)
//   0x1822e8b08 IHardwareMouseEventListener(see IHardwareMouseEventListener.h)
// Constructor: sub_181124858 (called by CUIManager ctor sub_181125C08,
//              allocation 0x58)
// Destructor:  via IActionListener slot [0] from CUIManager dtor sub_18112906C
// Size:        0x58
//
// Derived from CryEngine GameSDK Game/UI/UIInput.{h,cpp} (CUIInput) — but the
// Warhorse version dropped GameSDK's IUIGameEventSystem/IUIModule bases: it is
// a direct member of CUIManager (+0x10), NOT registered in the event-system
// map and NOT a FlashUI module.
//
// Ctor wiring (sub_181124858):
//  - m_pActionHandler: heap TActionHandler<CUIInput> (0x10); if empty, fills
//    ~55 handlers keyed by CGameActions members (*(S_GameContext+0x30) +
//    0x240..0x720, CCryName action ids) -> CUIInput member fns
//    (sub_181133EA8 "ui_up" family, sub_1804FE108, ...; values are 0x10-byte
//    multiple-inheritance member-fn pointers)
//  - registers as extra action listener: S_GameContext+8 ->vtbl+0xE0
//    (action-map host) ->vtbl+0x50 (this, 0)
//  - gEnv.pHardwareMouse (gEnv+0x110) ->vtbl+0x28 AddListener(this+0x10)
//  - m_pUIFunctions = pFlashUI->CreateEventSystem("Input", eEST_SYSTEM_TO_UI);
//    registers sender events (see E_UIInputEvent)
//  - m_pUIEvents = pFlashUI->CreateEventSystem("Input", eEST_UI_TO_SYSTEM);
//    m_pEventDispatcher->Init(m_pUIEvents, this, "UIInput"); registers receiver
//    event "ShowVirualKeyboard" (sic) (Title, InitialStr/"Value", MaxChars)
//    -> handler sub_181134584 (registration helper sub_18112212C)

namespace wh::guimodule {

// Sender events on the "Input" eEST_SYSTEM_TO_UI event system, in registration
// order (keys of m_eventSenderMap; value = engine id from RegisterEvent).
enum class E_UIInputEvent {
    OnKeyboardDone      = 0,  // param: String ("String of keyboard input"); sent by KeyboardFinished sub_181131AA8
    OnKeyboardCancelled = 1,  // sent by KeyboardCancelled sub_181131A74
};

class CUIInput
    : public Offsets::IActionListener             // +0x00  (3 slots)
    , public Offsets::IVirtualKeyboardEvents      // +0x08  (3 slots)
    , public Offsets::IHardwareMouseEventListener // +0x10  (2 slots)
{
public:
    TActionHandler<CUIInput>*                m_pActionHandler;   // +0x18  heap 0x10 (std::multimap head+size); action-id -> member fn
    SUIEventReceiverDispatcher<CUIInput>*    m_pEventDispatcher; // +0x20  heap 0x28
    Offsets::IUIEventSystem*                 m_pUIEvents;        // +0x28  "Input" eEST_UI_TO_SYSTEM (listener "UIInput")
    Offsets::IUIEventSystem*                 m_pUIFunctions;     // +0x30  "Input" eEST_SYSTEM_TO_UI
    std::map<E_UIInputEvent, unsigned int>   m_eventSenderMap;   // +0x38  game event -> engine event id (insert helper sub_180E318C4)
    uint64_t                                 m_unk48;            // +0x48  init 0xFFFFFFFFFFFFFFFF (xmmword_1830107A0)
    uint64_t                                 m_unk50;            // +0x50  init 0xFFFFFFFFFFFFFFFF

    // Overrides (vtables inherited, not re-declared):
    //   IActionListener::OnAction                    -> sub_180200140 (dispatches via m_pActionHandler)
    //   IVirtualKeyboardEvents::KeyboardCancelled    -> sub_181131A74 (sends OnKeyboardCancelled)
    //   IVirtualKeyboardEvents::KeyboardFinished     -> sub_181131AA8 (sends OnKeyboardDone)
    //   IHardwareMouseEventListener::OnHardwareMouseEvent -> sub_18050015C
};
static_assert(sizeof(CUIInput) == 0x58);

}  // namespace wh::guimodule
