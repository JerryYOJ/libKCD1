#include "combatmodule/C_CombatModule.h"
#include "game/S_GameContext.h"

wh::combatmodule::C_CombatModule* wh::combatmodule::C_CombatModule::GetInstance() {
    auto* ctx = wh::game::S_GameContext::GetInstance();
    return ctx ? ctx->m_pCombatModule : nullptr;
}
