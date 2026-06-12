#pragma once

#include <cstdint>
#include "Offsets/vtables/IUIGameEventSystem.h"
#include "Offsets/vtables/IUIEventSystem.h"
#include "guimodule/SUIEventReceiverDispatcher.h"
#include "guimodule/SUIEventSenderDispatcher.h"

// -----------------------------------------------
// C_UIKeybinds — key-rebinding settings screen ("Keybinds")
// -----------------------------------------------
// RTTI: .?AVC_UIKeybinds@guimodule@wh@@
// Constructor:     sub_1811284FC  (factory memsets 0x58 first)
// Factory:         sub_18112ABE4  (SAutoRegUIEventSystem<C_UIKeybinds>
//                  vtable 0x1822e8960; allocates 0x58, returns this+0)
// GetName:         sub_1806FE800  -> "UIKeybinds"
// InitEventSystem: sub_18112EC3C  (IUIGameEventSystem slot [2])
// Size:            0x58
//
// Inheritance (RTTI class-hierarchy descriptor): single base —
//   [+0x00] IUIGameEventSystem (: IUIPseudoRTTI)  (vtable 0x1826d1638)
//
// InitEventSystem (sub_18112EC3C):
//  A. creates system->UI IUIEventSystem "Keybinds" (direction 1), registers
//     events 0..3 (see E_UIKeybindsEvent; all use the dynamic/"Array" desc).
//  B. creates UI->system IUIEventSystem "Keybinds" (direction 0), registers
//     the receiver dispatcher as listener "C_UIKeybinds" with 7 functions
//     (registration order; every function takes controller(Int
//     "1=keyboard, 2=xboxpad, 4=ps4pad")):
//       "OnGetGroups"        handler sub_181134B14
//       "OnGetSuperactions"  handler sub_181134F54
//       "OnGetConflicts"     handler sub_181134ADC
//       "OnApplyChanges"     handler sub_181134178
//       "OnDiscardChanges"   handler sub_18113454C
//       "OnChangeInput"      + superactionId(String), slot(Int),
//                            action(Int "0=rebind, 1=clear, 2=default");
//                            registered via sub_1811227B8 (handler address is
//                            baked inside that template wrapper; the matching
//                            SUIEventDispatchFct4<C_UIKeybinds,void,int,
//                            CryStringT<char>,int,int> RTTI is @ 0x1822e8878)
//       "OnResetKeybinds"    handler sub_1811360D8
//     The simple handlers match SUIEventDispatchFct1<C_UIKeybinds,void,int>
//     RTTI @ 0x1822e8890.

namespace wh::guimodule {

// Flash event ids on the "Keybinds" system->UI event system (key = enum value
// passed to the m_eventSender map insert in sub_18112EC3C).
enum class E_UIKeybindsEvent {
    SetGroup       = 0x00,  // controller(Int), groupId(String), uiName(String), order(Int)
    SetSuperaction = 0x01,  // controller(Int), superactionId(String), groupId(String), order(Int), uiName(String), uiTooltip(String), slot1Input(String), slot2Input(String), changeable(Bool)
    SetConflict    = 0x02,  // controller(Int), superactionId(String), slot(Int), conflicts(Bool)
    ChangeInput    = 0x03,  // controller(Int), superactionId(String), slot(Int), input(String)
};

class C_UIKeybinds
    : public Offsets::IUIGameEventSystem        // +0x00  (: IUIPseudoRTTI)
{
public:
    // Embedded dispatcher (0x28: vtable 0x1826d15f8, mFunctionMap @+0x10,
    // m_pEventSystem @+0x20 = UI->system "Keybinds", m_pThis @+0x28).
    SUIEventReceiverDispatcher<C_UIKeybinds>
                              m_eventRecvDispatcher; // +0x08 .. 0x30

    SUIEventSenderDispatcher<E_UIKeybindsEvent>
                              m_eventSender;         // +0x30  (map @0x30, m_pEventSystem @0x40)
    Offsets::IUIEventSystem*  m_pUIEvents;           // +0x48  system->UI "Keybinds" (same object as m_eventSender.m_pEventSystem)
    Offsets::IUIEventSystem*  m_pUIFunctions;        // +0x50  UI->system "Keybinds"

    // Overrides (vtables inherited, not re-declared):
    //   IUIGameEventSystem::GetName          -> sub_1806FE800 ("UIKeybinds")
    //   IUIGameEventSystem::InitEventSystem  -> sub_18112EC3C
};
static_assert(sizeof(C_UIKeybinds) == 0x58);

}  // namespace wh::guimodule
