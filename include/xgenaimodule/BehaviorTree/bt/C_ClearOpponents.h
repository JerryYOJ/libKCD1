#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <ClearOpponents>.

namespace wh::xgenaimodule::BehaviorTree {

// <ClearOpponents>  RTTI C_ClearOpponents  vtable 0x1822268b8  size 0x28  base C_Node  ctx S_BaseNodeContext
class C_ClearOpponents : public C_NodeWrapper<C_ClearOpponents, C_Node, S_BaseNodeContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_ClearOpponents) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
