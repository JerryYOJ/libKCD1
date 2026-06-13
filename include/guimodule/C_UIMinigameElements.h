#pragma once
#include "Offsets/vtables/IFlashUI.h"

#include <cstdint>
#include "Offsets/vtables/I_MinigameElementsController.h"
#include "Offsets/vtables/IUIGameEventSystem.h"
// (individual UI includes consolidated into IFlashUI.h)

// -----------------------------------------------
// C_UIMinigameElements 鈥?minigame/book UI bridge ("UIMinigame")
// -----------------------------------------------
// RTTI: .?AVC_UIMinigameElements@guimodule@wh@@  (2 vtables: +0x00
// 0x1826d29e0, +0x08 0x1826d29f0)
// Constructor:     sub_181143B74
// Factory:         sub_181148394  (SAutoRegUIEventSystem<C_UIMinigameElements>
//                  vtable 0x1822ed1e0; allocates 0x48, returns this+8 鈥?the
//                  IUIGameEventSystem subobject CUIManager registers)
// GetName:         sub_1806FE840  -> "UIMinigame"
// InitEventSystem: sub_18114E0E4  (IUIGameEventSystem slot [2])
// Deleting dtor:   sub_181146CC8  (IUIGES [0] thunk sub_180B1AF58; the
//                  primary I_MinigameElementsController has NO virtual dtor)
// Size:            0x48
//
// Inheritance (RTTI class-hierarchy descriptor):
//   [+0x00] wh::guimodule::I_MinigameElementsController  (1 slot: setter of
//           m_value40, sub_1806F8740)
//   [+0x08] IUIGameEventSystem (: IUIPseudoRTTI)
//
// InitEventSystem (sub_18114E0E4):
//   1. UI->system IUIEventSystem "MinigameElements" (pFlashUI vtbl+0xC8,
//      direction 0) -> m_pUIFunctions; m_eventRecvDispatcher.Init(es, this,
//      "C_UIMinigameElements") (es->RegisterListener vtbl+0x20)
//   2. registers ONE UI->system function (dynamic-args desc, handler takes
//      SUIEvent const& 鈥?cf. RTTI vtable
//      SUIEventDispatchFct1<C_UIMinigameElements,void,SUIEvent const&>
//      @ 0x1822ecc08):
//        "OnBookPosition" 鈥?"Get information about book pages."
//            isPrev : Bool "If there is another page before the current page."
//            isNext : Bool "If there is another page after the current page."
//            + dynamic String array
//        handler: sub_1811515A4
// NO system->UI sender (no SUIEventSenderDispatcher member).

namespace wh::guimodule {

class C_UIMinigameElements
    : public Offsets::I_MinigameElementsController  // +0x00
    , public Offsets::IUIGameEventSystem            // +0x08  (: IUIPseudoRTTI)
{
public:
    // Embedded dispatcher (0x28: vtable 0x1826d27d8, mFunctionMap @+0x18,
    // m_pEventSystem @+0x28 = "MinigameElements" UI->system, m_pThis @+0x30).
    SUIEventReceiverDispatcher<C_UIMinigameElements>
                             m_eventRecvDispatcher; // +0x10 .. 0x38
    Offsets::IUIEventSystem* m_pUIFunctions;        // +0x38  same object as m_eventRecvDispatcher.m_pEventSystem
    int32_t  m_value40;                             // +0x40  ctor-init 0; written by I_MinigameElementsController vf[0] (semantic UNVERIFIED)
    char     _pad44[0x4];                           // +0x44

    // Overrides (vtables inherited, not re-declared):
    //   I_MinigameElementsController [0]     -> sub_1806F8740 (m_value40 setter)
    //   IUIGameEventSystem::GetName          -> sub_1806FE840 ("UIMinigame")
    //   IUIGameEventSystem::InitEventSystem  -> sub_18114E0E4
};
static_assert(sizeof(C_UIMinigameElements) == 0x48);

}  // namespace wh::guimodule
