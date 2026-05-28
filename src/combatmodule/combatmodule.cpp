#include "combatmodule/C_CombatModule.h"
#include "combatmodule/C_CombatScene.h"
#include "combatmodule/S_CombatSettings.h"
#include "combatmodule/C_CombatActionFactory.h"
#include "combatmodule/C_CombatActor.h"
#include "game/S_GameContext.h"
#include "Offsets/Offsets.h"

wh::combatmodule::C_CombatModule* wh::combatmodule::C_CombatModule::GetInstance() {
    auto* ctx = wh::game::S_GameContext::GetInstance();
    return ctx ? ctx->m_pCombatModule : nullptr;
}

wh::combatmodule::C_CombatScene* wh::combatmodule::C_CombatScene::GetInstance() {
    auto* mod = C_CombatModule::GetInstance();
    return mod ? mod->m_pCombatScene : nullptr;
}

wh::combatmodule::S_CombatSettings* wh::combatmodule::S_CombatSettings::GetInstance() {
    return reinterpret_cast<S_CombatSettings*>(Offsets::GetBase() + Offsets::kCombatSettingsOffset);
}

void* wh::combatmodule::C_CombatActionAttackFactory::CreateAndDispatch(
    void** ppOut, uint32_t inputClassId, int flags)
{
    using Fn = void*(__fastcall*)(C_CombatActionAttackFactory*, void**, uint32_t, int);
    auto fn = reinterpret_cast<Fn>(Offsets::GetBase() + Offsets::kCreateAndDispatchOffset);
    return fn(this, ppOut, inputClassId, flags);
}

void wh::combatmodule::C_CombatActor::DispatchCounterAction(
    I_CombatActorActionPtr* pOutAction, E_CounterActionType type, uint32_t scopeIndex)
{
    using Fn = void*(__fastcall*)(C_CombatActor*, I_CombatActorActionPtr*, int, uint32_t);
    auto fn = reinterpret_cast<Fn>(Offsets::GetBase() + Offsets::kDispatchCounterActionOffset);
    fn(this, pOutAction, static_cast<int>(type), scopeIndex);
}
