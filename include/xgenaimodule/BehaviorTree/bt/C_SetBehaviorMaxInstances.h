#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <SetBehaviorMaxInstances>.

namespace wh::xgenaimodule::BehaviorTree {

// <SetBehaviorMaxInstances>  RTTI C_SetBehaviorMaxInstances  vtable 0x182392cf0  size 0x28  base C_Node  ctx S_SetBehaviorMaxInstancesContext
struct S_SetBehaviorMaxInstancesContext;
class C_SetBehaviorMaxInstances : public C_NodeWrapper<C_SetBehaviorMaxInstances, C_Node, S_SetBehaviorMaxInstancesContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_SetBehaviorMaxInstances) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
