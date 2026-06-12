#pragma once

#include <cstdint>
#include <map>
#include "Offsets/vtables/ISystemEventListener.h"
#include "Offsets/vtables/IGameFrameworkListener.h"
#include "Offsets/vtables/IUIGameEventSystem.h"

// -----------------------------------------------
// CUIManager — Warhorse UI subsystem coordinator
// -----------------------------------------------
// RTTI: .?AVCUIManager@guimodule@wh@@  (2 vtables: +0x00 0x1822e8b90, +0x08 0x1822e8b40)
// Constructor: sub_181125C08
// Lazy-init:   sub_18112D540  (creates singleton on first access)
// GetInstance: sub_18020A504
// Destructor:  sub_181129B60  (scalar deleting; body sub_18112906C, frees 0x50)
// Global:      qword_182F77888
// Size:        0x50
//
// NOT CryEngine's CFlashUI/CUIManager (CryAction). This is the Warhorse
// game-logic coordinator (GameSDK Game/UI/UIManager.cpp lineage) that owns the
// five UI sub-controllers below and the registry of all auto-registered
// IUIGameEventSystem elements (C_UIMap, C_UIHUDElements, ...).
//
// Construction order (sub_181125C08):
//   1. m_pInput            = new CUIInput            (0x58, sub_181124858)
//   2. m_pSaveLoad         = new C_UISaveLoad        (0xE0, sub_181143CF4)
//   3. m_pMenuEvents       = new C_UIMenuEvents(0xC8, sub_1811425C8(this, m_pSaveLoad))
//   4. m_pInventoryActions = new C_UIInventoryActions(0x70, sub_181126124)
//   5. m_pGameEvents       = new CUIGameEvents       (0x60, sub_1811193B8)
//   6. InitEventSystems()  (sub_18113192C, see below)
//   7. pSystem->GetISystemEventDispatcher() (ISystem vtbl+0x248)
//        ->RegisterListener(this, "CUIManager", 1)        (dispatcher vtbl+0x08)
//      pGame->GetIGameFramework() (vtbl+0x78)
//        ->RegisterListener(this+8, "CUIManager", 2)      (framework vtbl+0x338,
//        priority 2 = FRAMEWORKLISTENERPRIORITY_HUD)
//
// InitEventSystems (sub_18113192C):
//   Walks the IUIEventSystemFactory intrusive list (s_pFirst =
//   qword_182F77880, node vtbl[1] = Create(), node+8 = m_pNext; see
//   guimodule/IUIEventSystemFactory.h). For each factory: creates the element,
//   keys it by element->GetName() (IUIGameEventSystem vtbl[1]) into
//   m_eventSystemMap (CryStringT key constructed by the misnamed
//   wh::framework::StringHash_18028CEA4 = CryStringT<char> ctor; map node
//   value at +0x28); duplicates are destroyed (vtbl[0](1)). Finally calls
//   InitEventSystem() (IUIGameEventSystem vtbl[2], +0x10) on every map entry.
//
// OnSystemEvent (sub_1806A2A24) — event ids per CryCommon/ISystem.h enum:
//   0x14 (LEVEL_LOAD_LOADINGSCREEN_ACTIVE) -> m_bLevelLoadStarted = false
//   0x15 (LEVEL_LOAD_START)                -> m_bLevelLoadStarted = true
//   0x21 (LANGUAGE_CHANGE)                 -> m_bLevelLoadStarted = true
//   0x3C (GLOBAL_SYSCMD_PAUSE)  -> menu re-show: if m_pMenuEvents->+0x43:
//        sub_181149264(0) / pFlashUI vtbl+0x40 / sub_181149264(1); else if
//        ->+0x41: sub_1805B84CC(0/1) + S_GameContext+0xB8 sub_180A85A80
//   0x40 (GLOBAL_SYSCMD_CHANGE_VIEW) -> if m_bLevelLoadStarted
//        sub_181154B30(m_pMenuEvents); then sub_181154ACC(sub_1806F7628())
//   (enum NAMES taken from the in-tree SDK ISystem.h; numeric ids are the
//   verified ground truth — KCD-specific enum drift not ruled out)
//
// OnPostUpdate (sub_1805F3848, called with this+8):
//   Iterates m_eventSystemMap and calls Update() (IUIGameEventSystem vtbl[5],
//   +0x28) on every registered element.
//
// Destructor body (sub_18112906C):
//   Unregisters from ISystemEventDispatcher (vtbl+0x10) and IGameFramework
//   (vtbl+0x340); sub_18112B000 (event-system map content teardown); deletes
//   m_pSaveLoad/m_pInput/m_pMenuEvents/m_pInventoryActions via their vtbl[0]
//   deleting dtors and m_pGameEvents via its vtbl[2]; frees the map sentinel
//   (0x30 bytes). NOTE: full module teardown (and the singleton Release,
//   qword_182F77888 = 0) lives in wh::guimodule::C_GUIModule vfunc
//   sub_181102B70 (vtable 0x1826cc850, slot [5]) — see
//   analysis/ui_infra/ui_managers.md.

// Auto-registered elements that live in the GLOBAL namespace (per RTTI):
class C_UICombatListener;
class C_UIActionHintManager;
class C_UIEventLog;

namespace wh::guimodule {

class CUIInput;
class C_UIMenuEvents;
class C_UIInventoryActions;
class CUIGameEvents;
class C_UISaveLoad;
class C_UIMap;
class C_UIHUDElements;
class CUIEntityDynTexTag;
class C_UIInventoryElements;
class C_UIKeybinds;
class C_UIInteractiveDialog;
class CUISettings;
class C_UISubtitles;
class C_UIRPGElements;
class C_UIMinigameElements;
class C_UIQuestLog;

class CUIManager
    : public Offsets::ISystemEventListener        // +0x00
    , public Offsets::IGameFrameworkListener      // +0x08
{
public:
    virtual void _ownVf0() {}                               // [3] 0x18  CUIManager's own virtual (empty stub)

    CUIInput*               m_pInput;                       // +0x10  (0x58, sub_181124858)
    C_UIMenuEvents*         m_pMenuEvents;                  // +0x18  (0xC8, sub_1811425C8 — gets m_pSaveLoad)
    C_UIInventoryActions*   m_pInventoryActions;            // +0x20  (0x70, sub_181126124)
    CUIGameEvents*          m_pGameEvents;                  // +0x28  (0x60, sub_1811193B8)
    C_UISaveLoad*           m_pSaveLoad;                    // +0x30  (0xE0, sub_181143CF4)

    // Element registry: GetName() -> auto-registered IUIGameEventSystem.
    // Key is a real CryStringT<char> (map insert path constructs it through
    // the misnamed "StringHash" CryStringT ctor; node layout: key +0x20,
    // value +0x28).
    std::map<CryStringT<char>, Offsets::IUIGameEventSystem*> m_eventSystemMap; // +0x38

    bool                    m_bLevelLoadStarted;            // +0x48  see OnSystemEvent notes (exact semantic name UNVERIFIED)
    char                    _pad49[7];                      // +0x49

    Offsets::IUIGameEventSystem* FindEventSystem(const char* name) {
        auto it = m_eventSystemMap.find(CryStringT<char>(name));
        return (it != m_eventSystemMap.end()) ? it->second : nullptr;
    }

    // The registry stores each element's IUIGameEventSystem SUBOBJECT pointer
    // (the factory returns `new T()` upcast — e.g. the C_UIHUDElements factory
    // sub_18111AB18 returns alloc+8). BaseOff = the IUIGameEventSystem base
    // offset within T (from each class header's RTTI banner); it must be
    // subtracted to recover T*.
    template<typename T, size_t BaseOff = 0>
    T* FindEventSystemAs(const char* name) {
        auto* p = FindEventSystem(name);
        return p ? reinterpret_cast<T*>(reinterpret_cast<char*>(p) - BaseOff) : nullptr;
    }

    // Typed accessors for every auto-registered element (registry key,
    // IUIGameEventSystem base offset — both verified per class header):
    C_UIMap*                GetUIMap()              { return FindEventSystemAs<C_UIMap>("UIMap"); }
    C_UIHUDElements*        GetHUDElements()        { return FindEventSystemAs<C_UIHUDElements, 0x08>("UIHelpBar"); }
    ::C_UIActionHintManager* GetActionHintManager() { return FindEventSystemAs<::C_UIActionHintManager>("ActionHintManager"); }
    ::C_UICombatListener*   GetCombatListener()     { return FindEventSystemAs<::C_UICombatListener, 0x08>("CombatListener"); }
    ::C_UIEventLog*         GetEventLog()           { return FindEventSystemAs<::C_UIEventLog, 0x08>("UIEventLog"); }
    CUIEntityDynTexTag*     GetEntityDynTexTag()    { return FindEventSystemAs<CUIEntityDynTexTag>("UIEntityDynTexTag"); }
    C_UIInventoryElements*  GetInventoryElements()  { return FindEventSystemAs<C_UIInventoryElements, 0x08>("UIInventoryController"); }
    C_UIKeybinds*           GetKeybinds()           { return FindEventSystemAs<C_UIKeybinds>("UIKeybinds"); }
    C_UIInteractiveDialog*  GetInteractiveDialog()  { return FindEventSystemAs<C_UIInteractiveDialog, 0x10>("UIInteractiveDialog"); }
    CUISettings*            GetSettings()           { return FindEventSystemAs<CUISettings, 0x10>("UISettings"); }
    C_UISubtitles*          GetSubtitles()          { return FindEventSystemAs<C_UISubtitles, 0x08>("UISubtitles"); }
    C_UIRPGElements*        GetRPGElements()        { return FindEventSystemAs<C_UIRPGElements, 0x08>("UIRPG"); }
    C_UIMinigameElements*   GetMinigameElements()   { return FindEventSystemAs<C_UIMinigameElements, 0x08>("UIMinigame"); }
    C_UIQuestLog*           GetQuestLog()           { return FindEventSystemAs<C_UIQuestLog, 0x08>("UIQuestLog"); }

    // Directly-owned sub-controllers (not in the map):
    CUIInput*             GetInput()            { return m_pInput; }
    C_UIMenuEvents*       GetMenuEvents()       { return m_pMenuEvents; }
    C_UIInventoryActions* GetInventoryActions() { return m_pInventoryActions; }
    CUIGameEvents*        GetGameEvents()       { return m_pGameEvents; }
    C_UISaveLoad*         GetSaveLoad()         { return m_pSaveLoad; }

    static CUIManager* GetInstance();               // Offsets.cpp (sub_18020A504)
};
static_assert(sizeof(CUIManager) == 0x50);

}  // namespace wh::guimodule
