#include <Windows.h>
#include "Offsets.h"
#include "crysystem/SSystemGlobalEnvironment.h"
#include "rpgmodule/C_RPGModule.h"
#include "guimodule/CUIManager.h"
#include "game/S_GameContext.h"
#include "combatmodule/C_CombatModule.h"
#include "combatmodule/C_CombatScene.h"
#include "combatmodule/S_CombatSettings.h"
#include "combatmodule/C_CombatActionFactory.h"
#include "combatmodule/C_CombatActor.h"
#include "rpgmodule/buff/C_BuffManager.h"

static uintptr_t GetBase() {
    static uintptr_t base = reinterpret_cast<uintptr_t>(GetModuleHandleA("WHGame.DLL"));
    return base;
}

// ---- CryEngine ----

SSystemGlobalEnvironment* SSystemGlobalEnvironment::GetInstance() {
    return reinterpret_cast<SSystemGlobalEnvironment*>(GetBase() + Offsets::kGEnvOffset);
}

Offsets::IGameFramework* Offsets::GetCCryAction() {
    return *reinterpret_cast<IGameFramework**>(GetBase() + kCCryActionOffset);
}

// ---- game ----

wh::game::S_GameContext* wh::game::S_GameContext::GetInstance() {
    return *reinterpret_cast<S_GameContext**>(GetBase() + Offsets::kGameContextOffset);
}

// ---- rpgmodule ----

wh::rpgmodule::C_RPGModule* wh::rpgmodule::C_RPGModule::GetInstance() {
    return *reinterpret_cast<C_RPGModule**>(GetBase() + Offsets::kRPGModuleOffset);
}

wh::rpgmodule::C_BuffManager* wh::rpgmodule::C_BuffManager::GetInstance() {
    return *reinterpret_cast<C_BuffManager**>(GetBase() + Offsets::kBuffManagerOffset);
}

// ---- guimodule ----

wh::guimodule::CUIManager* wh::guimodule::CUIManager::GetInstance() {
    return *reinterpret_cast<CUIManager**>(GetBase() + Offsets::kCUIManagerOffset);
}

// ---- combatmodule ----

wh::combatmodule::C_CombatModule* wh::combatmodule::C_CombatModule::GetInstance() {
    auto* ctx = wh::game::S_GameContext::GetInstance();
    return ctx ? ctx->m_pCombatModule : nullptr;
}

wh::combatmodule::C_CombatScene* wh::combatmodule::C_CombatScene::GetInstance() {
    auto* mod = C_CombatModule::GetInstance();
    return mod ? mod->m_pCombatScene : nullptr;
}

wh::combatmodule::S_CombatSettings* wh::combatmodule::S_CombatSettings::GetInstance() {
    return reinterpret_cast<S_CombatSettings*>(GetBase() + Offsets::kCombatSettingsOffset);
}

// ---- Action type IDs ----

#define ACTION_TYPE_GETTER(Name, Offset) \
    int32_t Offsets::ActionTypeId::Name() { \
        return *reinterpret_cast<int32_t*>(GetBase() + Offset); \
    }

ACTION_TYPE_GETTER(Attack,                      0x359B330)
ACTION_TYPE_GETTER(FreeAttack,                  0x359B334)
ACTION_TYPE_GETTER(Leap,                        0x359B338)
ACTION_TYPE_GETTER(MercyAttack,                 0x359B33C)
ACTION_TYPE_GETTER(Block,                       0x359B340)
ACTION_TYPE_GETTER(BlockMoveBack,               0x359B344)
ACTION_TYPE_GETTER(BlockStepBack,               0x359B348)
ACTION_TYPE_GETTER(PerfectBlock,                0x359B34C)
ACTION_TYPE_GETTER(PerfectNormalBlock,           0x359B350)
ACTION_TYPE_GETTER(RipostePerfectBlock,          0x359B354)
ACTION_TYPE_GETTER(PerfectBlockDodge,            0x359B358)
ACTION_TYPE_GETTER(SyncPerfectBlock,             0x359B35C)
ACTION_TYPE_GETTER(SyncPerfectBlockHit,          0x359B360)
ACTION_TYPE_GETTER(SyncDodge,                    0x359B364)
ACTION_TYPE_GETTER(SyncDodgeHit,                 0x359B368)
ACTION_TYPE_GETTER(SyncRiposte,                  0x359B36C)
ACTION_TYPE_GETTER(SyncRiposteHit,               0x359B370)
ACTION_TYPE_GETTER(HitTorso,                     0x359B374)
ACTION_TYPE_GETTER(HitBlockBroken,               0x359B378)
ACTION_TYPE_GETTER(HitBlockWeapon,               0x359B37C)
ACTION_TYPE_GETTER(HitMovement,                  0x359B380)
ACTION_TYPE_GETTER(GuardIdleUpperBody,            0x359B384)
ACTION_TYPE_GETTER(GuardSyncMovementMaster,       0x359B388)
ACTION_TYPE_GETTER(GuardSyncMovementSlave,        0x359B38C)
ACTION_TYPE_GETTER(GuardStartSyncMovementMaster,  0x359B390)
ACTION_TYPE_GETTER(GuardStartSyncMovementSlave,   0x359B394)
ACTION_TYPE_GETTER(Movement,                     0x359B398)
ACTION_TYPE_GETTER(GuardPreBlock,                0x359B39C)
ACTION_TYPE_GETTER(GuardAttackStart,             0x359B3A0)
ACTION_TYPE_GETTER(FailedAttackOnBlock,           0x359B3A4)
ACTION_TYPE_GETTER(FailedAttackOnPB,              0x359B3A8)
ACTION_TYPE_GETTER(SyncAttack,                   0x359B3AC)
ACTION_TYPE_GETTER(SyncHit,                      0x359B3B0)
ACTION_TYPE_GETTER(ComboAttack,                  0x359B3B4)
ACTION_TYPE_GETTER(ComboHit,                     0x359B3B8)
ACTION_TYPE_GETTER(StealthAttackSuccess,          0x359B3BC)
ACTION_TYPE_GETTER(StealthAttackFail,             0x359B3C0)
ACTION_TYPE_GETTER(StealthHitSuccess,             0x359B3C4)
ACTION_TYPE_GETTER(StealthHitFail,               0x359B3C8)
ACTION_TYPE_GETTER(SyncTransitionMaster,          0x359B3CC)
ACTION_TYPE_GETTER(SyncTransitionSlave,           0x359B3D0)
ACTION_TYPE_GETTER(HuntAttackMaster,             0x359B3D4)
ACTION_TYPE_GETTER(HuntAttackSlave,              0x359B3D8)

#undef ACTION_TYPE_GETTER

// ---- Input class IDs ----

#define INPUT_CLASS_GETTER(Name, Offset) \
    int32_t Offsets::InputClassId::Name() { \
        return *reinterpret_cast<int32_t*>(GetBase() + Offset); \
    }

INPUT_CLASS_GETTER(AttackLight,     0x359C2F0)
INPUT_CLASS_GETTER(AttackHeavy,     0x359C2F4)
INPUT_CLASS_GETTER(AttackSpecial,   0x359C2F8)
INPUT_CLASS_GETTER(MoveLeft,        0x359C2FC)
INPUT_CLASS_GETTER(MoveRight,       0x359C300)
INPUT_CLASS_GETTER(MoveBack,        0x359C304)
INPUT_CLASS_GETTER(MoveForward,     0x359C308)
INPUT_CLASS_GETTER(Block,           0x359C30C)

#undef INPUT_CLASS_GETTER

// ---- Combat factory methods ----

void* wh::combatmodule::C_CombatActionAttackFactory::CreateAndDispatch(
    void** ppOut, uint32_t inputClassId, int flags)
{
    using Fn = void*(__fastcall*)(C_CombatActionAttackFactory*, void**, uint32_t, int);
    auto fn = reinterpret_cast<Fn>(GetBase() + Offsets::kCreateAndDispatchOffset);
    return fn(this, ppOut, inputClassId, flags);
}

void wh::combatmodule::C_CombatActor::DispatchCounterAction(
    I_CombatActorActionPtr* pOutAction, E_CounterActionType type, uint32_t scopeIndex)
{
    using Fn = void*(__fastcall*)(C_CombatActor*, I_CombatActorActionPtr*, int, uint32_t);
    auto fn = reinterpret_cast<Fn>(GetBase() + Offsets::kDispatchCounterActionOffset);
    fn(this, pOutAction, static_cast<int>(type), scopeIndex);
}
