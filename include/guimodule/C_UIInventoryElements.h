#pragma once

#include <cstdint>
#include "Offsets/vtables/I_InventoryElementsController.h"
#include "Offsets/vtables/IUIGameEventSystem.h"
#include "Offsets/vtables/IUIEventSystem.h"
#include "guimodule/SUIEventSenderDispatcher.h"
#include "guimodule/SUIEventReceiverDispatcher.h"

// -----------------------------------------------
// C_UIInventoryElements — inventory popup dialogs ("UIInventoryController")
// -----------------------------------------------
// RTTI: .?AVC_UIInventoryElements@guimodule@wh@@
// Constructor:     sub_181128494
// Factory:         sub_18112AAEC  (SAutoRegUIEventSystem<C_UIInventoryElements>
//                  vtable 0x1822e8948; allocates 0x60, returns this+8 — the
//                  IUIGameEventSystem subobject CUIManager registers under
//                  "UIInventoryController")
// GetName:         sub_1806FE7F0  -> "UIInventoryController"
// InitEventSystem: sub_18112EA4C  (IUIGameEventSystem slot [2])
// Size:            0x60
//
// Inheritance (RTTI class-hierarchy descriptor):
//   [+0x00] wh::guimodule::I_InventoryElementsController (vtable 0x1826d1780,
//           2 slots: dtor + ShowInfoDialog)
//   [+0x08] IUIGameEventSystem (: IUIPseudoRTTI)         (vtable 0x1826d1798)
//
// InitEventSystem (sub_18112EA4C):
//   - creates system->UI IUIEventSystem "InventoryElements" (direction 1) and
//     registers one event (dynamic/"Array" desc):
//       [0] "ShowInfoDialog" — "Show info dialog"
//           Message : String "Message to be displayed"
//   - creates UI->system IUIEventSystem "InventoryElements" (direction 0) and
//     registers the receiver dispatcher as listener "C_UIInventoryElements".
//     NO UI->system functions are registered (the dispatcher function map
//     stays empty; listener registration only).
//
// I_InventoryElementsController::ShowInfoDialog (sub_1811399A8) copies the
// message and fires event [0] through m_eventSender (sub_181122F88).

namespace wh::guimodule {

// Flash event ids on the "InventoryElements" system->UI event system
// (registration order in sub_18112EA4C).
enum class E_UIInventoryElementsEvent {
    ShowInfoDialog = 0x00,   // Message(String)
};

class C_UIInventoryElements
    : public Offsets::I_InventoryElementsController  // +0x00
    , public Offsets::IUIGameEventSystem             // +0x08  (: IUIPseudoRTTI)
{
public:
    SUIEventSenderDispatcher<E_UIInventoryElementsEvent>
                              m_eventSender;         // +0x10  (map @0x10, m_pEventSystem @0x20)
    // Embedded dispatcher (0x28: vtable 0x1826d1618, mFunctionMap @+0x30,
    // m_pEventSystem @+0x40 = UI->system "InventoryElements", m_pThis @+0x48).
    SUIEventReceiverDispatcher<C_UIInventoryElements>
                              m_eventRecvDispatcher; // +0x28 .. 0x50
    Offsets::IUIEventSystem*  m_pUIEvents;           // +0x50  system->UI "InventoryElements" (NOT initialized by the ctor — only by InitEventSystem; factory does not memset)
    Offsets::IUIEventSystem*  m_pUIFunctions;        // +0x58  UI->system "InventoryElements" (same init caveat)

    // Overrides (vtables inherited, not re-declared):
    //   I_InventoryElementsController::Dtor           -> sub_181129BFC
    //   I_InventoryElementsController::ShowInfoDialog -> sub_1811399A8
    //   IUIGameEventSystem::GetName                   -> sub_1806FE7F0 ("UIInventoryController")
    //   IUIGameEventSystem::InitEventSystem           -> sub_18112EA4C
};
static_assert(sizeof(C_UIInventoryElements) == 0x60);

}  // namespace wh::guimodule
