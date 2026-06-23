#include "combatmodule/C_CombatScene.h"
#include "combatmodule/C_CombatModule.h"

wh::combatmodule::C_CombatScene* wh::combatmodule::C_CombatScene::GetInstance() {
    auto* mod = C_CombatModule::GetInstance();
    return mod ? mod->m_pCombatScene : nullptr;
}
