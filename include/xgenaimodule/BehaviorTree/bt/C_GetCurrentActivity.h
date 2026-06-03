#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <GetCurrentActivity>.

namespace wh::xgenaimodule::BehaviorTree {

// <GetCurrentActivity>  RTTI C_GetCurrentActivity  vtable 0x1822242d8  size 0x28  base C_Node  ctx S_GetCurrentActivityContext
struct S_GetCurrentActivityContext;
class C_GetCurrentActivity : public C_NodeWrapper<C_GetCurrentActivity, C_Node, S_GetCurrentActivityContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_GetCurrentActivity) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
