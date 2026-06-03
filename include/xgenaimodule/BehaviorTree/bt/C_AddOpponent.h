#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <AddOpponent>.

namespace wh::xgenaimodule::BehaviorTree {

// <AddOpponent>  RTTI C_AddOpponent  vtable 0x182216248  size 0x28  base C_Node  ctx S_AddOpponentContext
struct S_AddOpponentContext;
class C_AddOpponent : public C_NodeWrapper<C_AddOpponent, C_Node, S_AddOpponentContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_AddOpponent) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
