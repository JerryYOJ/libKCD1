#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <Fail>.

namespace wh::xgenaimodule::BehaviorTree {

// <Fail>  RTTI C_Fail  vtable 0x1821fa620  size 0x28  base C_Node  ctx S_BaseNodeContext
class C_Fail : public C_NodeWrapper<C_Fail, C_Node, S_BaseNodeContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_Fail) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
