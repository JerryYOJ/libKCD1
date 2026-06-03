#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <SetBehaviorState>.

namespace wh::xgenaimodule::BehaviorTree {

// <SetBehaviorState>  RTTI C_SetBehaviorState  vtable 0x182392960  size 0x28  base C_Node  ctx S_SetBehaviorStateContext
struct S_SetBehaviorStateContext;
class C_SetBehaviorState : public C_NodeWrapper<C_SetBehaviorState, C_Node, S_SetBehaviorStateContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_SetBehaviorState) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
