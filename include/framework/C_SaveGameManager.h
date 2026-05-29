#pragma once

#include <cstdint>
#include <ctime>
#include <vector>
#include "framework/I_ReadinessTask.h"
#include "framework/C_ReadinessObserver.h"
#include "framework/C_CrySaveGameHelper.h"
#include "framework/C_CryLoadGameHelper.h"
#include "../CryEngine/CryCommon/CryString.h"

namespace wh::framework {

// Save kinds dispatched through C_ModuleMessageSaveGameRequest::Dispatch (sub_180F08574)
// and executed by SaveGameToSlot. Names recovered verbatim from the debug overlay
// switch in sub_18020F49C.
enum class E_SaveType : int32_t {
    PermanentSave   = 0,   // permanent%03d.whs
    AutoSave        = 1,   // autosave%03d.whs
    ManualSave      = 2,   // save%03d.whs
    QuickSave       = 3,   // quicksave%03d.whs
    NewGame         = 4,   // initial save (no file)
    ExitSave        = 5,   // exit.whs
    LevelSwitchSave = 6,   // switch%05d.whs
    None            = 7,   // no save in progress (idle)
};

// Maximum number of save files per type (read-only global at 0x182662508)
//   [0] PermanentSave=30, [1] AutoSave=100, [2] ManualSave=10, [3] QuickSave=10,
//   [4] NewGame=0,        [5] ExitSave=1,   [6] LevelSwitchSave=20

// -----------------------------------------------
// S_SaveGameDescriptor — metadata for one persisted save file
// -----------------------------------------------
// Constructor: sub_180F0CCC8   Size: 0x80
// Allocated by sub_180F0CCA0, freed by sub_180F0DCEC (operator delete, 0x80).
// Populated by sub_180F130D4 at save time from game state + CVars.
struct S_SaveGameDescriptor {
    E_SaveType          m_type;                 // +0x00  save type
    int32_t             m_saveId;               // +0x04  unique save id within playline (-1 = unset)
    int32_t             m_nestedSaveId;         // +0x08  nested/parent save id (-1 = none)
    char                _pad0C[0x04];           // +0x0C
    __time64_t          m_timestamp;            // +0x10  epoch seconds (set via _time64)
    CryStringT<char>    m_levelName;            // +0x18  current level name at save time
    CryStringT<char>    m_questName;            // +0x20  quest/display name (or "[missing quest name]")
    CryStringT<char>    m_description;          // +0x28  "type|id|name|@location|time|date|playtime|"
    bool                m_installCompleted;     // +0x30  streaming install completed flag
    char                _pad31[0x03];           // +0x31
    int32_t             m_releaseVersion;       // +0x34  from CVar wh_sys_GameReleaseVersion
    int32_t             m_dlcFlags;             // +0x38  DLC bitmask
    bool                m_streamingCompleted;   // +0x3C
    char                _pad3D[0x03];           // +0x3D
    char                _pad40[0x18];           // +0x40  DLC-related data
    int32_t             m_playlineVersion;      // +0x58  playline format version
    char                _pad5C[0x04];           // +0x5C
    CryStringT<char>    m_filename;             // +0x60  e.g. "quicksave001.whs"
    char                _pad68[0x18];           // +0x68
};
static_assert(sizeof(S_SaveGameDescriptor) == 0x80);

// -----------------------------------------------
// S_SaveGameSlot — one playline's collection of save descriptors
// -----------------------------------------------
// Initialised as an array of 7 by the C_SaveGameManager constructor
// (sub_1804217C8, stride 0x38). Rescanned by UpdateSaveGameDescriptions.
struct S_SaveGameSlot {
    std::vector<S_SaveGameDescriptor*> m_entries;      // +0x00  pointers to heap-allocated descriptors
    int32_t             m_countPerType[7];              // +0x18  saves of each E_SaveType in this slot
    int32_t             m_nextSaveId;                   // +0x34  monotonic, bumped on each new save
};
static_assert(sizeof(S_SaveGameSlot) == 0x38);

// -----------------------------------------------
// C_SaveGameManager — orchestrates save/load slots and the CryEngine bridge
// -----------------------------------------------
// RTTI: .?AVC_SaveGameManager@framework@wh@@
// Vtable: 0x1826a31e8 (5 slots)   Constructor: sub_180F0CD58   Size: 0x230
//
// Derives I_ReadinessTask (single inheritance, verified via ??_R2 @ 0x18246abf8):
//   [0][1] I_ReadinessDebuggable debug hooks (stubbed)
//   [2]    IsReady       sub_180F101A4  -> returns m_afterGameLoad.m_registered == 0
//   [3]    GetTypeMask   sub_1806F9DA0  -> constant requirement mask
//   [4]    ~dtor         sub_180F0DD10  -> scalar deleting dtor (operator delete, 0x230)
//
// Owned by C_PlayerProfileWHManager (+0x28); reachable as
//   S_GameContext::GetInstance()->m_pPlayerProfileWHManager->m_pSaveGameManager
// Bridges to CryEngine save/load via C_CrySaveGameHelper / C_CryLoadGameHelper,
// also published as globals qword_1837879A8 / qword_1837879B0.

class C_SaveGameManager : public wh::I_ReadinessTask {
public:
    virtual ~C_SaveGameManager() = default;             // [4] introduces the virtual dtor

    // Core save routine (sub_180F12D64): serializes all modules into a save buffer,
    // writes the .whs file via WriteSaveFile, updates the slot's descriptor list.
    bool SaveGameToSlot(E_SaveType type, int32_t saveId = -1, const char* saveName);

    // Bottom of the save chain (sub_180F0F088): builds the .whs filename, asks
    // CryEngine for an ISaveGame, writes the buffer, and completes it.
    bool WriteSaveFile(void* saveBuffer, void* saveDescriptor, uint32_t replaceSlotIndex);

    S_SaveGameSlot      m_slots[7];         // +0x08  one per playline (7 * 0x38 = 0x188)
    void*               m_190;              // +0x190
    C_CrySaveGameHelper* m_pCrySaveHelper;  // +0x198  (also qword_1837879A8)
    C_CryLoadGameHelper* m_pCryLoadHelper;  // +0x1A0  (also qword_1837879B0)
    int32_t             m_miniGameSave;     // +0x1A8  CVar wh_sys_MiniGameSave
    int32_t             m_installCompleted; // +0x1AC  CVar wh_sys_GameSaveInstallCompleted
    int32_t             m_currentPlayline;  // +0x1B0  active playline index (0-6)
    int32_t             m_maxSaveSlotIndex; // +0x1B4  init 0x7FFFFFFF
    int32_t             m_nestedSaveId;     // +0x1B8  init -1, tracks nested save chain
    uint8_t             m_1BC;              // +0x1BC
    char                _pad1BD[0x03];      // +0x1BD
    C_ReadinessObserver m_afterGameLoad;    // +0x1C0  "AfterGameLoad" readiness gate (0x70)
};
static_assert(sizeof(C_SaveGameManager) == 0x230);

}  // namespace wh::framework
