#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_CombatNode.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <ClearTarget>.

namespace wh::xgenaimodule::BehaviorTree {

// <ClearTarget>  RTTI C_ClearTarget  vtable 0x1821f78f0  size 0x28  base C_CombatNode<C_Node>  ctx S_BaseNodeContext
class C_ClearTarget : public C_NodeWrapper<C_ClearTarget, C_CombatNode<C_Node>, S_BaseNodeContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_ClearTarget) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
