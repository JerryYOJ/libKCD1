#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <ForceIdleState>.

namespace wh::xgenaimodule::BehaviorTree {

// <ForceIdleState>  RTTI C_ForceIdleState  vtable 0x1823242d8  size 0x28  base C_Node  ctx S_ForceIdleStateContext
struct S_ForceIdleStateContext;
class C_ForceIdleState : public C_NodeWrapper<C_ForceIdleState, C_Node, S_ForceIdleStateContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_ForceIdleState) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
