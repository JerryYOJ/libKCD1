#pragma once

#include <cstdint>
#include <map>
#include <vector>
#include "Offsets/vtables/IUIModule.h"
#include "Offsets/vtables/I_ShadowPlayHightlightCountListener.h"
#include "Offsets/vtables/IUIEventSystem.h"
#include "Offsets/vtables/IConsole.h"
#include "guimodule/SUIEventReceiverDispatcher.h"

// -----------------------------------------------
// C_UIMenuEvents — main-menu / ingame-menu / inventory-screen flow
// -----------------------------------------------
// RTTI: .?AVC_UIMenuEvents@guimodule@wh@@  (2 vtables: +0x00 / +0x08)
//   0x1822ed1f8 IUIModule  — overrides: [0] dtor sub_181146C94,
//               [1] Init sub_18114B0C4, [4] Reset sub_181155910
//               ([6] EditorAllowReload inherits shared `return true`
//               sub_1806F8140)
//   0x1822ed240 I_ShadowPlayHightlightCountListener — [0] sub_181155770
// Constructor: sub_1811425C8(this, C_UISaveLoad*) — called by CUIManager ctor
//              sub_181125C08 (allocation 0xC8) AFTER C_UISaveLoad
// Size:        0xC8
//
// Registered as FlashUI module: pFlashUI->RegisterModule(this, "CUIMenuEvents")
// (IFlashUI [21] +0xA8). Derived from GameSDK Game/UI/UIMenuEvents.
//
// IUIModule::Init (sub_18114B0C4):
//  - registers callback sub_181151CE0 into the list at
//    *(S_GameContext+0xE8)+0xD0 (delegate wrapper sub_1802E7190(this))
//  - pushes this+8 (I_ShadowPlayHightlightCountListener subobject) into the
//    vector at *(S_GameContext+0x88)+0x30
// IUIModule::Reset (sub_181155910): sub_1805B84CC(this,0) (hide main menu),
//    sub_18114791C(this), sub_1811505D8(this,0)
//
// CUIManager::OnSystemEvent (sub_1806A2A24) drives this object on system
// event 0x3C: if byte+0x43 -> sub_181149264(0/1) around pFlashUI->vtbl+0x40,
// else if byte+0x41 -> sub_1805B84CC(0/1) + S_GameContext+0xB8 notification
// (sub_180A85A80); event 0x40 -> sub_181154B30(this).
//
// Ctor also resolves audio trigger ids (pSoundSystem vtbl+0x38):
//   "audio_setup_inventory_onepane" -> +0x84, "audio_setup_inventory" -> +0x88.

namespace wh::guimodule {

class C_UISaveLoad;

// Sender events on the "MenuEvents" eEST_SYSTEM_TO_UI event system, in
// registration order (= keys of m_eventSenderMap).
enum class E_UIMenuEvent {
    OnStartIngameMenu       = 0,
    OnStopIngameMenu        = 1,
    OnOpenInventory         = 2,  // InitParams: "Array with init parameters (mode, playerIdx, selectedIdx)"
    OnCloseInventory        = 3,
    OnRequestCloseInventory = 4,
    OnStartMainMenu         = 5,
    OnStopMainMenu          = 6,
    OnSwitchUser            = 7,  // "Triggered if user was switched (XBOX)"
    NVidiaShadowPlayStatus  = 8,  // params: Active, Records
};

class C_UIMenuEvents
    : public Offsets::IUIModule                          // +0x00
    , public Offsets::I_ShadowPlayHightlightCountListener // +0x08
{
public:
    C_UISaveLoad*                              m_pSaveLoad;        // +0x10  ctor arg (CUIManager::m_pSaveLoad)
    SUIEventReceiverDispatcher<C_UIMenuEvents>* m_pEventDispatcher; // +0x18  heap 0x28 (vtbl 0x1822ecd18)
    Offsets::IUIEventSystem*                   m_pUIEvents;        // +0x20  "MenuEvents" eEST_UI_TO_SYSTEM (listener "CUIMenuEvents")
    Offsets::IUIEventSystem*                   m_pUIFunctions;     // +0x28  "MenuEvents" eEST_SYSTEM_TO_UI
    std::map<E_UIMenuEvent, unsigned int>      m_eventSenderMap;   // +0x30

    uint8_t   m_unk40;                 // +0x40  init 0
    uint8_t   m_unk41;                 // +0x41  checked by CUIManager::OnSystemEvent 0x3C path (main-menu-shown flag, name UNVERIFIED)
    uint8_t   m_unk42;                 // +0x42
    uint8_t   m_unk43;                 // +0x43  checked by CUIManager::OnSystemEvent 0x3C path (ingame-menu-shown flag, name UNVERIFIED)
    uint8_t   m_unk44;                 // +0x44
    uint8_t   m_unk45;                 // +0x45
    char      _pad46[0x2];             // +0x46

    std::vector<uint64_t> m_unk48;     // +0x48  ctor reserves capacity >= 2 (grow helper sub_181093FDC)
    uint64_t  m_unk60;                 // +0x60  init 0
    uint16_t  m_unk68;                 // +0x68  init 0
    char      _pad6A[0x6];             // +0x6A
    uint32_t  m_unk70;                 // +0x70  init 0xF
    char      _pad74[0x4];             // +0x74
    uint64_t  m_unk78;                 // +0x78  init 0xFFFFFFFFFFFFFFFF (qword_183010900)
    uint32_t  m_unk80;                 // +0x80  init 0
    uint32_t  m_audioSetupInventoryOnepaneId; // +0x84  trigger id "audio_setup_inventory_onepane"
    uint32_t  m_audioSetupInventoryId; // +0x88  trigger id "audio_setup_inventory"
    uint32_t  m_unk8C;                 // +0x8C  init 0
    uint32_t  m_unk90;                 // +0x90  init 0
    char      _pad94[0x4];             // +0x94
    uint64_t  m_unk98;                 // +0x98  init 0
    uint64_t  m_unkA0;                 // +0xA0  init 0
    uint64_t  m_unkA8;                 // +0xA8  init 0
    uint32_t  m_unkB0;                 // +0xB0  init 0
    uint8_t   m_unkB4;                 // +0xB4  init 0
    char      _padB5[0x3];             // +0xB5

    Offsets::ICVar* m_pCVarMainMenuLayerProfile; // +0xB8  wh_ui_MainMenuLayerProfile ("main_menu")
    Offsets::ICVar* m_pCVarMainMenuSequence;     // +0xC0  wh_ui_MainMenuSequence ("mainMenuSequence")

    // Receiver events on "MenuEvents" (UI -> system), listener "CUIMenuEvents"
    // (registered in ctor via sub_18113C8E8):
    //   DisplayIngameMenu(Display)   -> sub_1805B849C
    //   DisplayMainMenu(Display)     -> sub_181151B80
    //   PrepareMainMenu              -> sub_181153508
    //   OnClosedInventory            -> sub_181151A58
    //   OnClosedCredits              -> sub_181151A30
    //   OnOpenedInventory            -> sub_181153380
    //   OnSendFeedback               -> empty handler (guard_check_icall_nop)
    //   ShowHighlight                -> sub_1811578C8
    //   GetNVidiaHighlightsState     -> sub_1805B9588
};
static_assert(sizeof(C_UIMenuEvents) == 0xC8);

}  // namespace wh::guimodule
