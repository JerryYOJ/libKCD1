#include "game/S_GameContext.h"
#include "Offsets/Offsets.h"
#include "entitymodule/C_Actor.h"

wh::game::S_GameContext* wh::game::S_GameContext::GetInstance() {
    static REL::Relocation<S_GameContext**> p{ REL::ID(870) };
    return *p;
}

wh::entitymodule::C_Actor* wh::game::S_GameContext::GetActorById(EntityId entityId) {
    if (!m_pActorSystem) return nullptr;
    auto* iactor = m_pActorSystem->GetActor(entityId);
    return reinterpret_cast<wh::entitymodule::C_Actor*>(iactor);
}
