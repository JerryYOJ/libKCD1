#pragma once

#include <cstdint>
#include "Offsets/vtables/I_SubtitlesController.h"
#include "Offsets/vtables/IUIGameEventSystem.h"
#include "Offsets/vtables/IUIEventSystem.h"
#include "Offsets/vtables/IConsole.h"
#include "guimodule/SUIEventSenderDispatcher.h"

// -----------------------------------------------
// C_UISubtitles — dialog subtitle text bridge ("UISubtitles")
// -----------------------------------------------
// RTTI: .?AVC_UISubtitles@guimodule@wh@@  (2 vtables: +0x00 0x1826d27f8,
// +0x08 0x1826d2818)
// Constructor:     inlined in the factory (no separate ctor function)
// Factory:         sub_181148680  (SAutoRegUIEventSystem<C_UISubtitles>
//                  vtable 0x1822ece38; allocates 0x38, returns this+8 — the
//                  IUIGameEventSystem subobject CUIManager registers)
// GetName:         sub_1806FE870  -> "UISubtitles"
// InitEventSystem: sub_18115034C  (IUIGameEventSystem slot [2])
// Deleting dtor:   sub_181146DF4
// Size:            0x38
//
// Inheritance (RTTI class-hierarchy descriptor):
//   [+0x00] wh::guimodule::I_SubtitlesController  (3 slots: dtor /
//           SetText(text,bForce) sub_1811577E8 / Clear sub_181147570)
//   [+0x08] IUIGameEventSystem (: IUIPseudoRTTI)
//
// InitEventSystem (sub_18115034C):
//   1. m_pCVarSubtitlesEnabled = GetCVar("wh_ui_SubtitlesEnabled")
//   2. creates the system->UI IUIEventSystem "Subtitles" (pFlashUI vtbl+0xC8,
//      direction 1) and registers one event:
//        [0] "OnText" — "triggered when subtitle text has changed"
//            Text : String "Multi lined HTML text"
//
// SetText (I_SubtitlesController [1], sub_1811577E8): if
// wh_ui_SubtitlesEnabled->GetIVal() || bForce || text empty — send
// OnText(text) through m_eventSender (sub_18113ED40), else send the clear
// form (sub_18113ECC4).

namespace wh::guimodule {

// Flash event ids on the "Subtitles" event system (registration order in
// sub_18115034C; id 0 is the literal map-insert key).
enum class E_UISubtitlesEvent {
    OnText = 0x00,   // Text:String "Multi lined HTML text"
};

class C_UISubtitles
    : public Offsets::I_SubtitlesController     // +0x00
    , public Offsets::IUIGameEventSystem        // +0x08  (: IUIPseudoRTTI)
{
public:
    SUIEventSenderDispatcher<E_UISubtitlesEvent>
                             m_eventSender;          // +0x10  (map @0x10, m_pEventSystem @0x20)
    Offsets::IUIEventSystem* m_pUIEvents;            // +0x28  "Subtitles" system->UI (same object as m_eventSender.m_pEventSystem)
    Offsets::ICVar*          m_pCVarSubtitlesEnabled;// +0x30  wh_ui_SubtitlesEnabled

    // Overrides (vtables inherited, not re-declared):
    //   I_SubtitlesController::SetText       -> sub_1811577E8
    //   I_SubtitlesController::Clear         -> sub_181147570
    //   IUIGameEventSystem::GetName          -> sub_1806FE870 ("UISubtitles")
    //   IUIGameEventSystem::InitEventSystem  -> sub_18115034C
};
static_assert(sizeof(C_UISubtitles) == 0x38);

}  // namespace wh::guimodule
