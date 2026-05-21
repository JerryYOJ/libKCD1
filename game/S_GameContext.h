#pragma once

#include <cstdint>

// -----------------------------------------------
// S_GameContext — Warhorse game module registry singleton
// -----------------------------------------------
// Global:      qword_1834FFD10  (RVA 0x4FFD10)
// Getter:      sub_180430AA4    (lazy-init)
// Constructor: sub_180DA70A0    (zeroes 0x170 bytes, no vtable)
// Init:        sub_18215EB90    (creates and registers all game modules)
// Size:        0x170
//
// A flat POD struct with no RTTI. Holds pointers to all Warhorse game modules.
// Module creation and registration verified via sub_18215EB90 decompilation.

namespace wh::rpgmodule { class C_RPGModule; }
namespace wh::playermodule { class C_PlayerModule; }
namespace wh::questmodule { class C_QuestModule; }

namespace wh::game {

struct S_GameContext {
    char                    _pad00[0x88];                   // +0x00
    void*                   m_pTelemetry;                   // +0x88  (0x50 bytes, sub_18216D118, conditional)
    void*                   m_pOPS;                         // +0x90  wh::game::C_OPS (0x20 bytes)
    char                    _pad98[0x18];                   // +0x98
    void*                   m_pModuleB0;                    // +0xB0  (0x188 bytes, sub_18103F5B0)
    void*                   m_pModuleB8;                    // +0xB8  (0x110 bytes, sub_181101EBC)
    void*                   m_pModuleC0;                    // +0xC0  (0x2F0 bytes, sub_180FAD8E0)
    void*                   m_pModuleC8;                    // +0xC8  (0xC8 bytes, sub_180F6C660)
    void*                   m_pModuleD0;                    // +0xD0  (0x98 bytes, sub_1812CA658)
    void*                   m_pModuleD8;                    // +0xD8  (0xE0 bytes, sub_1812A510C)
    questmodule::C_QuestModule* m_pQuestModule;             // +0xE0  (0x90 bytes)
    playermodule::C_PlayerModule* m_pPlayerModule;          // +0xE8  (0x110 bytes) VERIFIED
    rpgmodule::C_RPGModule* m_pRPGModule;                   // +0xF0  (0x5F0 bytes, sub_1811B9994) VERIFIED
    void*                   m_pModuleF8;                    // +0xF8  (0x580 bytes, sub_1810F2368)
    void*                   m_pFirstModule;                 // +0x100 (0x90 bytes, sub_180FE46CC)
    void*                   m_pModule108;                   // +0x108 (0x160 bytes, sub_180F36658)
    void*                   m_pModule110;                   // +0x110 (0xA8 bytes, sub_180FDEBA8)
    void*                   m_pModule118;                   // +0x118 (0x680 bytes, sub_181606174)
    char                    _pad120[0x50];                  // +0x120
};
static_assert(sizeof(S_GameContext) == 0x170);

}  // namespace wh::game
