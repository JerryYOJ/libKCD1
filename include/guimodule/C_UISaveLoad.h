#pragma once

#include <cstdint>
#include <map>
#include "Offsets/vtables/IUIModule.h"
#include "Offsets/vtables/IUIEventSystem.h"
#include "Offsets/vtables/IConsole.h"
#include "guimodule/SUIEventReceiverDispatcher.h"
#include "framework/C_ReadinessObserver.h"

// -----------------------------------------------
// C_UISaveLoad — savegame / playline / new-game flash <-> game bridge
// -----------------------------------------------
// RTTI: .?AVC_UISaveLoad@guimodule@wh@@  (single vtable @ 0x1822ed138)
//   IUIModule — overrides: [0] dtor sub_181146DC0, [1] Init sub_18114B380
//   (the IDA name wh::guimodule::C_UISaveLoad::DispatchPreparingNewGame_18114B380
//   is MISLEADING: it is IUIModule::Init — it SUBSCRIBES a "PreparingNewGame"
//   observer from *(S_GameContext+0xB8)+0xE8 into m_pPreparingNewGameHook
//   (+0xC0) via sub_181140ED8/sub_1811469A0)
// Constructor: sub_181143CF4 — called by CUIManager ctor sub_181125C08
//              (allocation 0xE0), constructed BEFORE C_UIMenuEvents which
//              receives a pointer to it
// Size:        0xE0
//
// Registered as FlashUI module:
//   pFlashUI->RegisterModule(this, "C_UISaveLoad") (IFlashUI [21] +0xA8).
// The +0xC0 subscription object (0x20 bytes) is freed during module teardown
// by wh::guimodule::C_GUIModule vfunc sub_181102B70 (vtable 0x1826cc850 [5]),
// which reaches it through CUIManager::GetInstance()->m_pSaveLoad.
//
// CVars registered in ctor (value storage INSIDE this object for the int
// cvars; ICVar* kept only for the string one):
//   wh_sys_NoPlaylineDeleting (+0x2C), wh_sys_NoSavePotion (+0x30),
//   wh_mod_ShowUsedModsInSaveTooltip (+0x34),
//   wh_sys_ShowVersionInSaveTooltip (+0x38), wh_sys_ShowDlcInSaveTooltip
//   (+0x3C), wh_sys_LoadGameFilter (+0x40, default -1),
//   wh_ui_DisableNewGameDebugFader (+0x44), wh_ui_NewGameVideoFile (+0x48,
//   default "/videos/q_skalitz/cin_7805_stribrna_skalice.usm").

namespace wh::guimodule {

// Sender events on the "SaveLoad" eEST_SYSTEM_TO_UI event system, in
// registration order (= keys of m_eventSenderMap).
enum class E_UISaveLoadEvent {
    OnGetPlaylinesItem  = 0,  // PlaylineId, Name, Data, Tooltip, Disabled
    OnGetSavedGamesItem = 1,  // Name, SaveId, Tooltip, Disabled
    OnGameSaved         = 2,
    OnGameSaveFinished  = 3,  // "Triggered after the gamesave has been done"
    OnGameLoaded        = 4,  // Result
    OnCanSave           = 5,  // Id, DisableSave, Reason
    OnCanLoad           = 6,  // Id, Tooltip, DisableLoad
    OnNewGamePrepared   = 7,  // Result
    OnGameplayStart     = 8,
};

class C_UISaveLoad
    : public Offsets::IUIModule                  // +0x00
{
public:
    void*                                      m_pUnk08;            // +0x08  = *(S_GameContext+0x50) (save/profile system, identity UNVERIFIED)
    SUIEventReceiverDispatcher<C_UISaveLoad>*  m_pEventDispatcher;  // +0x10  heap 0x28 (vtbl 0x1822eccf8)
    Offsets::IUIEventSystem*                   m_pUIEvents;         // +0x18  "SaveLoad" eEST_UI_TO_SYSTEM (listener "C_UISaveLoad")
    Offsets::IUIEventSystem*                   m_pUIFunctions;      // +0x20  "SaveLoad" eEST_SYSTEM_TO_UI
    int32_t   m_unk28;                          // +0x28  init 1
    int32_t   m_noPlaylineDeleting;             // +0x2C  cvar wh_sys_NoPlaylineDeleting
    int32_t   m_noSavePotion;                   // +0x30  cvar wh_sys_NoSavePotion
    int32_t   m_showUsedModsInSaveTooltip;      // +0x34  cvar wh_mod_ShowUsedModsInSaveTooltip
    int32_t   m_showVersionInSaveTooltip;       // +0x38  cvar wh_sys_ShowVersionInSaveTooltip
    int32_t   m_showDlcInSaveTooltip;           // +0x3C  cvar wh_sys_ShowDlcInSaveTooltip
    int32_t   m_loadGameFilter;                 // +0x40  cvar wh_sys_LoadGameFilter (init -1; save-type bitmask)
    int32_t   m_disableNewGameDebugFader;       // +0x44  cvar wh_ui_DisableNewGameDebugFader
    Offsets::ICVar* m_pCVarNewGameVideoFile;    // +0x48  wh_ui_NewGameVideoFile

    wh::C_ReadinessObserver m_beforeNewGameObserver; // +0x50  gate name "BeforeNewGame" (ctor sub_180F0025C)

    void*     m_pPreparingNewGameHook;          // +0xC0  0x20-byte "PreparingNewGame" subscription, set by Init sub_18114B380; freed by C_GUIModule shutdown sub_181102B70
    uint64_t  m_unkC8;                          // +0xC8  init 0
    std::map<E_UISaveLoadEvent, unsigned int> m_eventSenderMap; // +0xD0

    // Receiver events on "SaveLoad" (UI -> system), listener "C_UISaveLoad"
    // (registered in ctor; handlers where the registration passes one):
    //   LoadDefaultLevel                                   -> sub_181153038
    //   UpdateSavedGames                                   -> sub_181154CFC
    //   GetPlaylines(FilterMask, SkipEmpty, NewestSaveGameOnly)
    //   GetSavedGames(FilterMask, PlayLine)
    //   LoadSavedGame(SaveId, PlayLine)                    -> sub_181153090
    //   DeleteSavedGame(SaveId, PlayLine)                  -> sub_181151AE4
    //   DeleteAllSavedGames                                -> sub_181151A78
    //   SetPlayline(PlayLine)        [gated on sys_FreezePlayline]
    //   LoadLastSavedGame
    //   SaveGame(SaveType, OverwriteSaveId, UsePotion)
    //   SaveNewGame
    //   PrepareNewGame(GameMode, Perks)
    //   NewGameStarted(Debug)
    //   CanSave(Id, IsExitSave)
    //   CanLoad(Id, FilterMask, PlayLine, NewestSaveGameOnly)
    //   ChangeProfile
    //   IsNewGame -> returns Result ("true if the level was loaded the first time")
    //   GetPlaylineCount -> returns Count
    //   ReEnableExitSaveLoading
};
static_assert(sizeof(C_UISaveLoad) == 0xE0);

}  // namespace wh::guimodule
