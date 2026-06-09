#pragma once

#include <cstdint>
#include <map>
#include "Offsets/vtables/ISystemEventListener.h"
#include "Offsets/vtables/IGameFrameworkListener.h"
#include "Offsets/vtables/IUIGameEventSystem.h"

// -----------------------------------------------
// CUIManager — Warhorse UI subsystem coordinator
// -----------------------------------------------
// RTTI: .?AVCUIManager@guimodule@wh@@  (2 vtables: +0x00, +0x08)
// Constructor: sub_181125C08
// Lazy-init:   sub_18112D540  (creates singleton on first access)
// Destructor:  sub_181129B60  (frees 0x50 bytes)
// Global:      qword_182F77888
// Size:        0x50
//
// NOT CryEngine's CUIManager (CryAction/FlashUI). This is a Warhorse
// game-logic coordinator that owns UI subsystems and ticks them per-frame.
// CryEngine's IUIManager (Flash element lifecycle) is accessed separately
// through qword_1829D17E8.
//
// Inheritance (binary layout):
//   [+0x00] ISystemEventListener     — level load/unload, editor events
//   [+0x08] IGameFrameworkListener    — per-frame OnPostUpdate tick
//
// OnSystemEvent (sub_1806A2A24) handles:
//   0x14 (LEVEL_UNLOAD_START) → m_bLevelLoaded = false
//   0x15 (LEVEL_POST_UNLOAD)  → m_bLevelLoaded = true
//   0x22 (EDITOR_ON_INIT)     → reinit through m_pMenuEvents
//   0x3D (LEVEL_GAMEPLAY_START)
//   0x41                      → conditional reload
//
// OnPostUpdate (sub_1805F3848):
//   Iterates m_eventSystemMap, calls Update() on each registered
//   IUIGameEventSystem (including C_UIMap).
//
// Registered with CryEngine as "CUIManager" on both ISystem and IGameFramework.

namespace wh::guimodule {

class CUIInput;
class C_UIMenuEvents;
class C_UIInventoryActions;
class CUIGameEvents;
class C_UISaveLoad;
class C_UIMap;
class C_UIHUDElements;

class CUIManager
    : public Offsets::ISystemEventListener       // +0x00
    , public Offsets::IGameFrameworkListener      // +0x08
{
public:
    virtual void _ownVf0() {}                               // [3] 0x18  CUIManager's own virtual (empty stub)

    CUIInput*               m_pInput;                       // +0x10  (0x58 bytes, sub_181124858)
    C_UIMenuEvents*         m_pMenuEvents;                  // +0x18  (0xC8 bytes, sub_1811425C8)
    C_UIInventoryActions*   m_pInventoryActions;            // +0x20  (0x70 bytes, sub_181126124)
    CUIGameEvents*          m_pGameEvents;                  // +0x28  (0x60 bytes, sub_1811193B8)
    C_UISaveLoad*           m_pSaveLoad;                    // +0x30  (0xE0 bytes, sub_181143CF4)
    std::map<const char*, Offsets::IUIGameEventSystem*, CStrLess> m_eventSystemMap; // +0x38
    bool                    m_bLevelLoaded;                 // +0x48  set by OnSystemEvent (0=unloaded, 1=loaded)
    char                    _pad49[7];                      // +0x49

    Offsets::IUIGameEventSystem* FindEventSystem(const char* name) {
        auto it = m_eventSystemMap.find(name);
        return (it != m_eventSystemMap.end()) ? it->second : nullptr;
    }

    template<typename T>
    T* FindEventSystemAs(const char* name) {
        return reinterpret_cast<T*>(FindEventSystem(name));
    }

    C_UIMap* GetUIMap() { return FindEventSystemAs<C_UIMap>("UIMap"); }
    C_UIHUDElements* GetHUDElements() { return FindEventSystemAs<C_UIHUDElements>("UIHelpBar"); }

    static CUIManager* GetInstance();               // Offsets.cpp
};
static_assert(sizeof(CUIManager) == 0x50);

}  // namespace wh::guimodule
