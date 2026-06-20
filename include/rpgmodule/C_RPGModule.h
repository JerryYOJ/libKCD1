#pragma once

#include <cstdint>
#include "../framework/C_BaseModule.h"             // +0x00 primary base (its vtables land at +0x00 and +0x78)
#include "../framework/C_ParallelModuleUpdater.h"  // +0x88 secondary base (its vtable lands at +0x88)
#include "C_SoulList.h"
#include "C_FactionManager.h"
#include "S_RpgParams.h"

// -----------------------------------------------
// C_RPGModule — RPG module singleton
// -----------------------------------------------
// RTTI: .?AVC_RPGModule@rpgmodule@wh@@
// Inheritance (RTTI base array): C_RPGModule : wh::framework::C_BaseModule (+0x00 -- primary vtable @0
//   and its I_ModuleMessageListener secondary vtable @+0x78), wh::framework::C_ParallelModuleUpdater
//   (+0x88 -- vtable @+0x88). Those two bases account for all THREE vtables; C_RPGModule's own
//   members begin at +0x548.
// Constructor: sub_1811B9994
// Size: 0x5F0 (module allocator requests exactly 0x5F0 before constructor)
// Global: qword_1835AC728 (set at end of constructor)
// NOTE: sub_18022877C returns the C_FactionManager singleton, NOT the RPG module.
//
// Constructor allocates sub-objects (type confirmed by the vtable each ctor stores):
//   0x1000F0 → C_SoulList            → a1[0xA9] = +0x548
//   0x48     → (unknown)             → a1[0xAA] = +0x550  (sub_1811677F8)
//   0x08     → C_RPGDialog           → a1[0xAB] = +0x558
//   0x1430   → (unknown)             → a1[0xAC] = +0x560  (sub_1811B988C)
//   0x08     → C_RPGQuest            → a1[0xAD] = +0x568
//   0xD0     → (unknown)             → a1[0xAE] = +0x570
//   0x40     → C_EventManager        → a1[0xAF] = +0x578
//   0x298    → C_RPGLocationManager  → a1[0xB0] = +0x580  (ctor sub_18118DCC8) [VERIFIED]
//
// See also:
//   C_SoulList.h       — entity→soul lookup (0x1000F0 bytes)
//   C_FactionManager.h — faction/reputation state (separate singleton)
//   S_RpgParams.h      — tuning parameter array (separate singleton)

namespace wh::rpgmodule {

class C_SoulList;
class C_RPGLocationManager;   // +0x580 (defined in C_RPGLocationManager.h)
class C_RPGDialog;            // +0x558
class C_RPGQuest;             // +0x568
class C_EventManager;         // +0x578

class C_RPGModule : public wh::framework::C_BaseModule,            // +0x00 (0x88)
                    public wh::framework::C_ParallelModuleUpdater   // +0x88 (0x4C0)
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_RPGModule;

    // ---- own members (the two bases span +0x00 .. +0x548) ----
    C_SoulList*           m_pSoulList;          // +0x548  soul lookup (0x1000F0 bytes, sub_1811F1490)
    void*                 m_pUnk550;            // +0x550  (0x48 bytes, sub_1811677F8) [type UNVERIFIED]
    C_RPGDialog*          m_pRPGDialog;         // +0x558  (0x08; ctor sets C_RPGDialog vtable)
    void*                 m_pUnk560;            // +0x560  (0x1430 bytes, sub_1811B988C) [type UNVERIFIED]
    C_RPGQuest*           m_pRPGQuest;          // +0x568  (0x08; ctor sets C_RPGQuest vtable)
    void*                 m_pUnk570;            // +0x570  (0xD0 bytes) [type UNVERIFIED]
    C_EventManager*       m_pEventManager;      // +0x578  (0x40; ctor sets C_EventManager vtable)
    C_RPGLocationManager* m_pLocationManager;   // +0x580  (0x298; ctor sub_18118DCC8) [VERIFIED]

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
