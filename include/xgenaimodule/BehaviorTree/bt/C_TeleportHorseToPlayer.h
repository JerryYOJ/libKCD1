#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <TeleportHorseToPlayer>.

namespace wh::xgenaimodule::BehaviorTree {

// <TeleportHorseToPlayer>  RTTI C_TeleportHorseToPlayer  vtable 0x182347610  size 0x28  base C_Node  ctx S_TeleportHorseToPlayerContext
struct S_TeleportHorseToPlayerContext;
class C_TeleportHorseToPlayer : public C_NodeWrapper<C_TeleportHorseToPlayer, C_Node, S_TeleportHorseToPlayerContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_TeleportHorseToPlayer) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
