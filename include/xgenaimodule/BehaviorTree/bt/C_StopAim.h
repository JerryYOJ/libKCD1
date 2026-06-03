#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <StopAim>.

namespace wh::xgenaimodule::BehaviorTree {

// <StopAim>  RTTI C_StopAim  vtable 0x1823585d0  size 0x28  base C_Node  ctx S_BaseNodeContext
class C_StopAim : public C_NodeWrapper<C_StopAim, C_Node, S_BaseNodeContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_StopAim) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
