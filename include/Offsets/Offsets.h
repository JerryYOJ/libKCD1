#pragma once
#include <cstdint>
#include <cstddef>
#include "REL.h"   // REL::ID / REL::Relocation / REL::Module (address resolution)
#include "vtables/IGameFramework.h"
#include "vtables/I3DEngine.h"

// -----------------------------------------------
// Global singleton offsets
// -----------------------------------------------
// Getter declarations are on each class as static GetInstance() methods.
// All implementations are in Offsets.cpp / the class .cpp, each embedding its
// Steam-RVA id inline via REL::ID(0x...) (CommonLib REL idiom). There is no
// central offset-constant table anymore — the id lives at the call site.
//
//   SSystemGlobalEnvironment::GetInstance()          — crysystem/SSystemGlobalEnvironment.h
//   wh::game::S_GameContext::GetInstance()           — game/S_GameContext.h
//   wh::rpgmodule::C_RPGModule::GetInstance()        — rpgmodule/C_RPGModule.h
//   wh::guimodule::CUIManager::GetInstance()         — guimodule/CUIManager.h
//   wh::guimodule::uielement::C_UIEHud::GetInstance() — guimodule/C_UIEHud.h
//   wh::combatmodule::C_CombatModule::GetInstance()  — combatmodule/C_CombatModule.h
//   wh::combatmodule::C_CombatScene::GetInstance()   — combatmodule/C_CombatScene.h
//   wh::combatmodule::S_CombatSettings::GetInstance() — combatmodule/S_CombatSettings.h
//   wh::rpgmodule::C_BuffManager::GetInstance()        — rpgmodule/buff/C_BuffManager.h
//   wh::rpgmodule::S_RpgParamValues::Get()             — rpgmodule/S_RpgParams.h
//   wh::rpgmodule::S_RpgParamDefs::Get()               — rpgmodule/S_RpgParams.h

namespace Offsets {

// WHGame.dll base address helper (== REL::Module::base()).
uintptr_t GetBase();

// CryAction has no RE'd header — getter stays here
IGameFramework* GetCCryAction();

// I3DEngine: gEnv.p3DEngine (+0x08) is a DEAD SDK slot in KCD (always null) — read
// the Cry3DEngineBase static C3DEngine* instead (set in the C3DEngine ctor).
I3DEngine* Get3DEngine();

// CryEngine bucket allocator forwarders (the candidate std::vector's heap path).
// CryMemAlloc -> sub_18028C040 (bucket pool malloc); CryMemFree -> CryEngine::MemFree
// (sub_1805B72C0, SIZED). Matched pair — do NOT free these with CryModuleFree (CRT free),
// which would corrupt the bucket heap.
void* CryMemAlloc(std::size_t size);
void  CryMemFree(void* p, std::size_t size);

// -----------------------------------------------
// Combat action type IDs (runtime-assigned globals)
// -----------------------------------------------
// Registered in C_CombatActionTypeDatabase::Init (sub_18071C6E4). Each ID is
// assigned at startup via BST insertion — NOT compile-time constants. The backing
// array starts at RVA 0x359B330; getters read array[index] (impl in Offsets.cpp).
struct ActionTypeId {
    static int32_t Attack();                    // [0]
    static int32_t FreeAttack();                // [1]
    static int32_t Leap();                      // [2]
    static int32_t MercyAttack();               // [3]
    static int32_t Block();                     // [4]
    static int32_t BlockMoveBack();             // [5]
    static int32_t BlockStepBack();             // [6]
    static int32_t PerfectBlock();              // [7]
    static int32_t PerfectNormalBlock();        // [8]
    static int32_t RipostePerfectBlock();       // [9]
    static int32_t PerfectBlockDodge();         // [10]
    static int32_t SyncPerfectBlock();          // [11]
    static int32_t SyncPerfectBlockHit();       // [12]
    static int32_t SyncDodge();                 // [13]
    static int32_t SyncDodgeHit();              // [14]
    static int32_t SyncRiposte();               // [15]
    static int32_t SyncRiposteHit();            // [16]
    static int32_t HitTorso();                  // [17]
    static int32_t HitBlockBroken();            // [18]
    static int32_t HitBlockWeapon();            // [19]
    static int32_t HitMovement();               // [20]
    static int32_t GuardIdleUpperBody();        // [21]
    static int32_t GuardSyncMovementMaster();   // [22]
    static int32_t GuardSyncMovementSlave();    // [23]
    static int32_t GuardStartSyncMovementMaster(); // [24]
    static int32_t GuardStartSyncMovementSlave();  // [25]
    static int32_t Movement();                  // [26]
    static int32_t GuardPreBlock();             // [27]
    static int32_t GuardAttackStart();          // [28]
    static int32_t FailedAttackOnBlock();       // [29]
    static int32_t FailedAttackOnPB();          // [30]
    static int32_t SyncAttack();                // [31]
    static int32_t SyncHit();                   // [32]
    static int32_t ComboAttack();               // [33]
    static int32_t ComboHit();                  // [34]
    static int32_t StealthAttackSuccess();      // [35]
    static int32_t StealthAttackFail();         // [36]
    static int32_t StealthHitSuccess();         // [37]
    static int32_t StealthHitFail();            // [38]
    static int32_t SyncTransitionMaster();      // [39]
    static int32_t SyncTransitionSlave();       // [40]
    static int32_t HuntAttackMaster();          // [41]
    static int32_t HuntAttackSlave();           // [42]
};

// -----------------------------------------------
// Combat input class IDs (runtime-assigned globals)
// -----------------------------------------------
// Registered in C_CombatInputClassDatabase::Init (sub_18071EA94). Backing array
// starts at RVA 0x359C2F0. Names from StringHash calls in the init function.
struct InputClassId {
    static int32_t AttackLight();               // [0] "attack_light"
    static int32_t AttackHeavy();               // [1] "attack_heavy"
    static int32_t AttackSpecial();             // [2] "attack_special"
    static int32_t MoveLeft();                  // [3] "move_left"
    static int32_t MoveRight();                 // [4] "move_right"
    static int32_t MoveBack();                  // [5] "move_back"
    static int32_t MoveForward();               // [6] "move_forward"
    static int32_t Block();                     // [7] "block"
};

}  // namespace Offsets
