#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <TeleportFormationToSpots>.

namespace wh::xgenaimodule::BehaviorTree {

// <TeleportFormationToSpots>  RTTI C_TeleportFormationToSpots  vtable 0x18236dc90  size 0x28  base C_Node  ctx S_TeleportFormationToSpotsContext
struct S_TeleportFormationToSpotsContext;
class C_TeleportFormationToSpots : public C_NodeWrapper<C_TeleportFormationToSpots, C_Node, S_TeleportFormationToSpotsContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_TeleportFormationToSpots) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
