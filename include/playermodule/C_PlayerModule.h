#pragma once

#include <cstdint>
#include "framework/C_BaseModule.h"
#include "Offsets/vtables/ISystemEventListener.h"

// -----------------------------------------------
// C_PlayerModule — player systems module
// -----------------------------------------------
// RTTI: .?AVC_PlayerModule@playermodule@wh@@
// Constructor: sub_1812816E4
// Size: 0x110
// Stored at S_GameContext+0xE8 (VERIFIED via sub_18215EB90)
//
// Inheritance (from RTTI base-class array ??_R2 @ 0x1824f8cb8):
//   [+0x00] C_BaseModule → C_Graph → S_Graph → S_Job  primary vtable 0x1826e5328
//   [+0x78] I_ModuleMessageListener                    vtable 0x1826e5308
//   [+0x88] ISystemEventListener                       vtable 0x1826e5340
//
// The game's autosave-via-sleeping mechanism sets m_autoSaveRequested = true.
// The per-frame tick (sub_18020FE50) checks it, clears it, and dispatches
// E_SaveType::AutoSave through C_PlayerProfileWHManager::Dispatch.

namespace wh::playermodule {

class C_FastTravel;
class C_FOWManager;
class C_RandomEventManager;
class C_SkipTimeDatabase;
class C_Keybinds;
class C_ActionHintManager;
class C_GameOver;
class C_BlockSourcesManager;

class C_PlayerModule
    : public wh::framework::C_BaseModule
    , public Offsets::ISystemEventListener
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_PlayerModule;

    uint16_t*               m_pModuleFlags;         // +0x90  (2-byte alloc, init 0)
    C_FOWManager*           m_pFOWManager;          // +0x98  fog of war manager (0x78 bytes)
    void*                   m_pSkipTimeDB;          // +0xA0  C_SkipTimeDatabase (0x30 bytes)
    void*                   m_pMinigameManager;     // +0xA8  (0x50 bytes, sub_18128288C)
    C_FastTravel*           m_pFastTravel;          // +0xB0  (0x188 bytes) VERIFIED
    C_RandomEventManager*   m_pRandomEventManager;  // +0xB8  (0xA8 bytes)
    void*                   m_pUnkC0;               // +0xC0  (0xA0 bytes, sub_18121BED4)
    C_Keybinds*             m_pKeybinds;            // +0xC8  (0x1E8 bytes)
    void*                   m_pGameOver;            // +0xD0  C_GameOver (0x68 bytes)
    void*                   m_pSignalD8;            // +0xD8  C_Signal<> (0x70 bytes)
    C_ActionHintManager*    m_pActionHintManager;   // +0xE0  (0x170 bytes)
    void*                   m_pUnkE8;               // +0xE8  (0x58 bytes, sub_18122D374)
    void*                   m_pUnkF0;               // +0xF0  (0x40 bytes, sub_18122D9C8)
    void*                   m_pUnkF8;               // +0xF8  (0x10 bytes, container)
    C_BlockSourcesManager*  m_pBlockSourcesMgr;     // +0x100 (0x10 bytes)
    bool                    m_autoSaveRequested;    // +0x108 set by SaveGameViaResting, cleared in tick
    char                    _pad109[0x7];           // +0x109
};
static_assert(sizeof(C_PlayerModule) == 0x110);

}  // namespace wh::playermodule
