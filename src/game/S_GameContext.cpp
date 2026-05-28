#include "game/S_GameContext.h"
#include "Offsets/Offsets.h"

wh::game::S_GameContext* wh::game::S_GameContext::GetInstance() {
    return *reinterpret_cast<S_GameContext**>(Offsets::GetBase() + Offsets::kGameContextOffset);
}
