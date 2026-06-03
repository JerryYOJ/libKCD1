#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <NotSeenByPlayer>.

namespace wh::xgenaimodule::BehaviorTree {

// <NotSeenByPlayer>  RTTI C_NotSeenByPlayer  vtable 0x1823324a8  size 0x28  base C_Node  ctx S_NotSeenByPlayerContext
struct S_NotSeenByPlayerContext;
class C_NotSeenByPlayer : public C_NodeWrapper<C_NotSeenByPlayer, C_Node, S_NotSeenByPlayerContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_NotSeenByPlayer) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
