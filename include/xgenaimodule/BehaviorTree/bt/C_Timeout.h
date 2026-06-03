#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Decorator.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <Timeout>.

namespace wh::xgenaimodule::BehaviorTree {

// <Timeout>  RTTI C_Timeout  vtable 0x182376b88  size 0x30  base C_Decorator  ctx S_TimeoutContext
struct S_TimeoutContext;
class C_Timeout : public C_NodeWrapper<C_Timeout, C_Decorator, S_TimeoutContext>
{
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_Timeout) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
