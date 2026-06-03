#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Decorator.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <Invertor>.

namespace wh::xgenaimodule::BehaviorTree {

// <Invertor>  RTTI C_Invertor  vtable 0x1822049d0  size 0x30  base C_Decorator  ctx S_BaseNodeContext
class C_Invertor : public C_NodeWrapper<C_Invertor, C_Decorator, S_BaseNodeContext>
{
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_Invertor) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
