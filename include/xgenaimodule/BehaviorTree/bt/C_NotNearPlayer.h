#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <NotNearPlayer>.

namespace wh::xgenaimodule::BehaviorTree {

// <NotNearPlayer>  RTTI C_NotNearPlayer  vtable 0x182216728  size 0x28  base C_Node  ctx S_NotNearPlayerContext
struct S_NotNearPlayerContext;
class C_NotNearPlayer : public C_NodeWrapper<C_NotNearPlayer, C_Node, S_NotNearPlayerContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_NotNearPlayer) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
