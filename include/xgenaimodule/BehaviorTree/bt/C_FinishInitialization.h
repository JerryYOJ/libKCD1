#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <FinishInitialization>.

namespace wh::xgenaimodule::BehaviorTree {

// <FinishInitialization>  RTTI C_FinishInitialization  vtable 0x182324430  size 0x28  base C_Node  ctx S_BaseNodeContext
class C_FinishInitialization : public C_NodeWrapper<C_FinishInitialization, C_Node, S_BaseNodeContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_FinishInitialization) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
