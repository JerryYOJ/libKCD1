#pragma once

#include <cstdint>
#include "C_SoulList.h"
#include "C_FactionManager.h"
#include "S_RpgParams.h"

// -----------------------------------------------
// C_RPGModule — RPG module singleton
// -----------------------------------------------
// RTTI: .?AVC_RPGModule@rpgmodule@wh@@  (3 vtables: primary, +0x78, +0x88)
// Constructor: sub_1811B9994
// Size: 0x5F0 (module allocator requests exactly 0x5F0 before constructor)
// Global: qword_1835AC728 (set at end of constructor)
// NOTE: sub_18022877C returns the C_FactionManager singleton, NOT the RPG module.
//
// Constructor allocates sub-objects:
//   0x1000F0 → C_SoulList         → a1[0xA9] = +0x548
//   0x48     → (unknown)          → a1[0xAA] = +0x550  (sub_1811677F8)
//   0x08     → C_RPGDialog        → a1[0xAB] = +0x558
//   0x1430   → (unknown)          → a1[0xAC] = +0x560  (sub_1811B988C)
//   0x08     → C_RPGQuest         → a1[0xAD] = +0x568
//   0xD0     → (unknown)          → a1[0xAE] = +0x570
//   0x40     → C_EventManager     → a1[0xAF] = +0x578
//   0x298    → (unknown)          → a1[0xB0] = +0x580  (sub_18118DCC8)
//
// See also:
//   C_SoulList.h       — entity→soul lookup (0x1000F0 bytes)
//   C_FactionManager.h — faction/reputation state (separate singleton)
//   S_RpgParams.h      — tuning parameter array (separate singleton)

namespace wh::rpgmodule {

class C_SoulList;

class C_RPGModule {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_RPGModule;
    // +0x00..+0x77: primary vtable + module base fields
    char            _pad00[0x78];
    // +0x78: secondary vtable (C_RPGModule _0)
    // +0x88: secondary vtable (C_RPGModule _1)
    char            _pad78[0x4D0];

    C_SoulList*     m_pSoulList;                // +0x548  soul lookup (0x1000F0 bytes, sub_1811F1490)
    void*           m_pUnk550;                  // +0x550  (0x48 bytes, sub_1811677F8)
    void*           m_pRPGDialog;               // +0x558  C_RPGDialog (0x08 bytes, just vtable)
    void*           m_pUnk560;                  // +0x560  (0x1430 bytes, sub_1811B988C)
    void*           m_pRPGQuest;                // +0x568  C_RPGQuest (0x08 bytes, just vtable)
    void*           m_pUnk570;                  // +0x570  (0xD0 bytes)
    void*           m_pEventManager;            // +0x578  C_EventManager (0x40 bytes)
    void*           m_pUnk580;                  // +0x580  (0x298 bytes, sub_18118DCC8)

    uint64_t        m_unk588;                   // +0x588  (zeroed)
    uint64_t        m_unk590;                   // +0x590  (zeroed)
    uint64_t        m_unk598;                   // +0x598  (zeroed)
    uint64_t        m_unk5A0;                   // +0x5A0  (zeroed)
    uint64_t        m_unk5A8;                   // +0x5A8  (zeroed)
    uint64_t        m_unk5B0;                   // +0x5B0  (zeroed)
    uint64_t        m_unk5B8;                   // +0x5B8  (zeroed)
    uint64_t        m_unk5C0;                   // +0x5C0  (zeroed)
    uint64_t        m_unk5C8;                   // +0x5C8  (skipped in ctor init, a1[0xB9])
    uint64_t        m_unk5D0;                   // +0x5D0  (zeroed)
    uint64_t        m_unk5D8;                   // +0x5D8  (zeroed)
    uint64_t        m_unk5E0;                   // +0x5E0  (zeroed)
    uint64_t        m_unk5E8;                   // +0x5E8  (zeroed)

    static C_RPGModule* GetInstance();              // Offsets.cpp
};
static_assert(sizeof(C_RPGModule) == 0x5F0);

}  // namespace wh::rpgmodule
