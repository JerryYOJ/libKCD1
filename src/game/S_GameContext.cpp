#include "game/S_GameContext.h"
#include "Offsets/Offsets.h"
#include "entitymodule/C_Actor.h"

wh::game::S_GameContext* wh::game::S_GameContext::GetInstance() {
    return *reinterpret_cast<S_GameContext**>(Offsets::GetBase() + Offsets::kGameContextOffset);
}

wh::entitymodule::C_Actor* wh::game::S_GameContext::GetActorById(EntityId entityId) {
    if (!m_pActorSystem) return nullptr;
    auto* iactor = m_pActorSystem->GetActor(entityId);
    return reinterpret_cast<wh::entitymodule::C_Actor*>(iactor);
}
