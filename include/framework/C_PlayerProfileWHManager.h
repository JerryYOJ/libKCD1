#pragma once

#include <cstdint>
#include <vector>
#include "framework/I_ReadinessTask.h"
#include "framework/C_ReadinessObserver.h"
#include "framework/C_SaveGameManager.h"
#include "Offsets/vtables/ISystemEventListener.h"

namespace wh::framework {

// -----------------------------------------------
// C_PlayerProfileWHManager — owns the save system and player profile
// -----------------------------------------------
// RTTI: .?AVC_PlayerProfileWHManager@framework@wh@@
// Constructor: sub_180F06200
// Created in game init sub_180EF9C7C, stored at S_GameContext+0x50.
// Size: 0xF0
//
// Multiple inheritance (verified via RTTI base-class array ??_R2 @ 0x18246a4a8):
//   [+0x00] I_ReadinessTask  (: I_ReadinessDebuggable)  primary vtable 0x1826a2318 (4 slots)
//   [+0x08] ISystemEventListener                        vtable 0x1826a22f8 (3 slots)
//     OnSystemEvent (sub_180697F88) reacts to event 0x40 by flushing the save
//     descriptions (C_SaveGameManager::UpdateSaveGameDescriptions).
//
// Save requests run a small state machine in Dispatch (sub_180F08574): a request
// is accepted only while m_activeSaveType == None (7); it is then set to the
// requested E_SaveType and a C_ModuleMessageSaveGameRequest is dispatched.

class C_PlayerProfileWHManager
    : public wh::I_ReadinessTask
    , public Offsets::ISystemEventListener
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_PlayerProfileWHManager;
    // Run the pending save request (sub_180F095F0): forwards m_activeSaveType /
    // m_saveParam / m_pSaveName to m_pSaveGameManager->SaveGameToSlot, broadcasts the
    // post-save module message, then returns the manager to the idle (None) state.
    void ExecuteSave();

    void*               unk10;                   // +0x10  (set post-construction)
    CryStringT<char>*   m_pProfileName;         // +0x18  heap CryString, defaults to empty
    void*               m_pSaveListenerList;    // +0x20  -> {0x48-byte intrusive list head, 0}
    C_SaveGameManager*  m_pSaveGameManager;     // +0x28  (0x230 bytes, sub_180F0CD58)
    char                _pad30[0x30];           // +0x30
    std::vector<void*>* m_pPendingSaveOps;      // +0x60  must be empty for a request to start
    E_SaveType          m_activeSaveType;       // +0x68  None (7) when idle
    int32_t             m_saveParam;            // +0x6C  request param (slot/playline; -1 = none)
    CryStringT<char>*   m_pSaveName;            // +0x70  heap CryString, forced save name
    int32_t             m_nestedSaveId;         // +0x78  set to 5 on ExitSave; init -1
    char                _pad7C[0x04];           // +0x7C
    C_ReadinessObserver m_beforeGameSave;       // +0x80  "BeforeGameSave" readiness gate (0x70)
};
static_assert(sizeof(C_PlayerProfileWHManager) == 0xF0);

}  // namespace wh::framework
