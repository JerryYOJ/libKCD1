#pragma once

#include <cstdint>
#include "../Offsets/vtables/IActorSystem.h"

// -----------------------------------------------
// S_GameContext — Warhorse game module registry singleton
// -----------------------------------------------
// Global:      qword_1834FFD10  (RVA 0x4FFD10)
// Getter:      sub_180430AA4    (lazy-init)
// Constructor: sub_180DA70A0    (zeroes 0x170 bytes, no vtable)
// Init:        sub_180EF9C7C    (creates framework-level objects)
//              sub_18215EB90    (creates and registers all game modules)
// Size:        0x170
//
// A flat POD struct with no RTTI. Holds pointers to all Warhorse game modules.

namespace wh::framework {
    class C_PlayerProfileWHManager;
    class C_ModulesManager;
}
namespace wh::combatmodule { class C_CombatModule; }
namespace wh::rpgmodule { class C_RPGModule; }
namespace wh::playermodule { class C_PlayerModule; }
namespace wh::questmodule { class C_QuestModule; }
namespace wh::animationmodule { class C_AnimationModule; }
namespace wh::entitymodule { class C_EntityModule; }
namespace wh::environmentmodule { class C_EnvironmentModule; }
namespace wh::guimodule { class C_GUIModule; }
namespace wh::soundmodule { class C_SoundModule; }
namespace wh::databasemodule { class C_DatabaseModule; }
namespace wh::dialogmodule { class C_DialogModule; }
namespace wh::utilsmodule { class C_UtilsModule; }
namespace wh::shopmodule { class C_ShopModule; }
namespace wh::xgenaimodule { class C_XGenAIModule; }

namespace wh::game {

struct S_GameContext {
    void*                                   m_pGame;                    // +0x00  C_Game ptr (from qword_18378D5C8)
    void*                                   m_pFramework;               // +0x08  IGameFramework / CCryAction
    char                                    _pad10[0x10];               // +0x10
    void*                                   m_pConfig;                  // +0x20  0x958 bytes config/state struct
    void*                                   m_28;                       // +0x28
    char                                    _pad30[0x20];               // +0x30
    framework::C_PlayerProfileWHManager*    m_pPlayerProfileWHManager;  // +0x50  (0xF0 bytes) owns C_SaveGameManager
    void*                                   m_58;                       // +0x58  (0x20 bytes, sub_180F00030)
    void*                                   m_60;                       // +0x60  (0x478 bytes, sub_180EE3288)
    void*                                   m_68;                       // +0x68  (0x40 bytes, sub_180EE3184)
    void*                                   m_70;                       // +0x70  (0x60 bytes, sub_180F000AC)
    char                                    _pad78[0x10];               // +0x78
    void*                                   m_pTelemetry;               // +0x88  (0x50 bytes, conditional)
    void*                                   m_pOPS;                     // +0x90  wh::game::C_OPS (0x20 bytes)
    framework::C_ModulesManager*            m_pModulesManager;          // +0x98  (0xD8 bytes) dispatches C_ModuleMessage
    void*                                   m_A0;                       // +0xA0  (0x18 bytes)
    void*                                   m_A8;                       // +0xA8
    entitymodule::C_EntityModule*           m_pEntityModule;            // +0xB0  (0x188 bytes)
    guimodule::C_GUIModule*                 m_pGUIModule;               // +0xB8  (0x110 bytes)
    animationmodule::C_AnimationModule*     m_pAnimationModule;         // +0xC0  (0x2F0 bytes)
    combatmodule::C_CombatModule*           m_pCombatModule;            // +0xC8  (0xC8 bytes)
    soundmodule::C_SoundModule*             m_pSoundModule;             // +0xD0  (0x98 bytes)
    shopmodule::C_ShopModule*               m_pShopModule;              // +0xD8  (0xE0 bytes)
    questmodule::C_QuestModule*             m_pQuestModule;             // +0xE0  (0x90 bytes)
    playermodule::C_PlayerModule*           m_pPlayerModule;            // +0xE8  (0x110 bytes)
    rpgmodule::C_RPGModule*                 m_pRPGModule;               // +0xF0  (0x5F0 bytes)
    environmentmodule::C_EnvironmentModule* m_pEnvironmentModule;       // +0xF8  (0x580 bytes)
    utilsmodule::C_UtilsModule*             m_pUtilsModule;             // +0x100 (0x90 bytes)
    databasemodule::C_DatabaseModule*       m_pDatabaseModule;          // +0x108 (0x160 bytes, stored as ptr+0x88)
    dialogmodule::C_DialogModule*           m_pDialogModule;            // +0x110 (0xA8 bytes)
    xgenaimodule::C_XGenAIModule*           m_pXGenAIModule;            // +0x118 (0x680 bytes)
    void*                                   m_120;                      // +0x120
    Offsets::IActorSystem*                  m_pActorSystem;             // +0x128 CActorSystem (CryEngine)
    char                                    _pad130[0x40];              // +0x130

    static S_GameContext* GetInstance();
};
static_assert(sizeof(S_GameContext) == 0x170);

}  // namespace wh::game
