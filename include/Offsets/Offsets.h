#pragma once
#include <cstdint>
#include "vtables/IGameFramework.h"

// -----------------------------------------------
// Global singleton offsets
// -----------------------------------------------
// Getter declarations are on each class as static GetInstance() methods.
// All implementations are in Offsets.cpp.
//
//   SSystemGlobalEnvironment::GetInstance()          — crysystem/SSystemGlobalEnvironment.h
//   wh::game::S_GameContext::GetInstance()           — game/S_GameContext.h
//   wh::rpgmodule::C_RPGModule::GetInstance()        — rpgmodule/C_RPGModule.h
//   wh::guimodule::CUIManager::GetInstance()         — guimodule/CUIManager.h
//   wh::combatmodule::C_CombatModule::GetInstance()  — combatmodule/C_CombatModule.h
//   wh::combatmodule::C_CombatScene::GetInstance()   — combatmodule/C_CombatScene.h
//   wh::combatmodule::S_CombatSettings::GetInstance() — combatmodule/S_CombatSettings.h
//   wh::rpgmodule::C_BuffManager::GetInstance()        — rpgmodule/buff/C_BuffManager.h

namespace Offsets {

// WHGame.dll base address helper
uintptr_t GetBase();

inline static constexpr uintptr_t kGEnvOffset              = 0x29D16B8;
inline static constexpr uintptr_t kCCryActionOffset         = 0x3785D88;
inline static constexpr uintptr_t kRPGModuleOffset          = 0x35AC728;
inline static constexpr uintptr_t kCUIManagerOffset         = 0x2F77888;
inline static constexpr uintptr_t kGameContextOffset        = 0x4FFD10;
inline static constexpr uintptr_t kCombatSettingsOffset     = 0x36DD8A0;
inline static constexpr uintptr_t kRPGParamsOffset          = 0x35004A0;
inline static constexpr uintptr_t kActionTypeDbOffset       = 0x359B1E0;
inline static constexpr uintptr_t kBuffManagerOffset        = 0x3500F10;
inline static constexpr uintptr_t kCreateAndDispatchOffset  = 0x460934;
inline static constexpr uintptr_t kDispatchCounterActionOffset = 0x69536C;
inline static constexpr uintptr_t kTypeFactoryEntryInitOffset  = 0x712B68;
inline static constexpr uintptr_t kActionTypeIdBase         = 0x359B330;
inline static constexpr uintptr_t kInputClassIdBase         = 0x359C2F0;
inline static constexpr uintptr_t kExecuteSaveOffset        = 0xF095F0; // C_PlayerProfileWHManager::ExecuteSave
inline static constexpr uintptr_t kSaveGameToSlotOffset     = 0xF12D64; // C_SaveGameManager::SaveGameToSlot
inline static constexpr uintptr_t kWriteSaveFileOffset      = 0xF0F088; // C_SaveGameManager::WriteSaveFile

// CryAction has no RE'd header — getter stays here
IGameFramework* GetCCryAction();

// -----------------------------------------------
// Combat action type IDs (runtime-assigned globals)
// -----------------------------------------------
// Registered in C_CombatActionTypeDatabase::Init (sub_18071C6E4).
// Each ID is assigned at startup via BST insertion — NOT compile-time constants.
// Read from globals the same way game code does.
struct ActionTypeId {
    static int32_t Attack();                    // 0x359B330
    static int32_t FreeAttack();                // 0x359B334
    static int32_t Leap();                      // 0x359B338
    static int32_t MercyAttack();               // 0x359B33C
    static int32_t Block();                     // 0x359B340
    static int32_t BlockMoveBack();             // 0x359B344
    static int32_t BlockStepBack();             // 0x359B348
    static int32_t PerfectBlock();              // 0x359B34C
    static int32_t PerfectNormalBlock();        // 0x359B350
    static int32_t RipostePerfectBlock();       // 0x359B354
    static int32_t PerfectBlockDodge();         // 0x359B358
    static int32_t SyncPerfectBlock();          // 0x359B35C
    static int32_t SyncPerfectBlockHit();       // 0x359B360
    static int32_t SyncDodge();                 // 0x359B364
    static int32_t SyncDodgeHit();              // 0x359B368
    static int32_t SyncRiposte();               // 0x359B36C
    static int32_t SyncRiposteHit();            // 0x359B370
    static int32_t HitTorso();                  // 0x359B374
    static int32_t HitBlockBroken();            // 0x359B378
    static int32_t HitBlockWeapon();            // 0x359B37C
    static int32_t HitMovement();               // 0x359B380
    static int32_t GuardIdleUpperBody();        // 0x359B384
    static int32_t GuardSyncMovementMaster();   // 0x359B388
    static int32_t GuardSyncMovementSlave();    // 0x359B38C
    static int32_t GuardStartSyncMovementMaster(); // 0x359B390
    static int32_t GuardStartSyncMovementSlave();  // 0x359B394
    static int32_t Movement();                  // 0x359B398
    static int32_t GuardPreBlock();             // 0x359B39C
    static int32_t GuardAttackStart();          // 0x359B3A0
    static int32_t FailedAttackOnBlock();       // 0x359B3A4
    static int32_t FailedAttackOnPB();          // 0x359B3A8
    static int32_t SyncAttack();                // 0x359B3AC
    static int32_t SyncHit();                   // 0x359B3B0
    static int32_t ComboAttack();               // 0x359B3B4
    static int32_t ComboHit();                  // 0x359B3B8
    static int32_t StealthAttackSuccess();      // 0x359B3BC
    static int32_t StealthAttackFail();         // 0x359B3C0
    static int32_t StealthHitSuccess();         // 0x359B3C4
    static int32_t StealthHitFail();            // 0x359B3C8
    static int32_t SyncTransitionMaster();      // 0x359B3CC
    static int32_t SyncTransitionSlave();       // 0x359B3D0
    static int32_t HuntAttackMaster();          // 0x359B3D4
    static int32_t HuntAttackSlave();           // 0x359B3D8
};

// -----------------------------------------------
// Combat input class IDs (runtime-assigned globals)
// -----------------------------------------------
// Registered in C_CombatInputClassDatabase::Init (sub_18071EA94).
// Each ID is assigned at startup via BST insertion.
// VERIFIED: names from StringHash calls in the init function.
struct InputClassId {
    static int32_t AttackLight();               // 0x359C2F0  "attack_light"
    static int32_t AttackHeavy();               // 0x359C2F4  "attack_heavy"
    static int32_t AttackSpecial();             // 0x359C2F8  "attack_special"
    static int32_t MoveLeft();                  // 0x359C2FC  "move_left"
    static int32_t MoveRight();                 // 0x359C300  "move_right"
    static int32_t MoveBack();                  // 0x359C304  "move_back"
    static int32_t MoveForward();               // 0x359C308  "move_forward"
    static int32_t Block();                     // 0x359C30C  "block"
};

}  // namespace Offsets
