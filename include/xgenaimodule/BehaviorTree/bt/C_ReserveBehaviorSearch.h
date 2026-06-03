#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Decorator.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <ReserveBehaviorSearch>.

namespace wh::xgenaimodule::BehaviorTree {

// <ReserveBehaviorSearch>  RTTI C_ReserveBehaviorSearch  vtable 0x182208840  size 0x30  base C_Decorator  ctx S_BaseNodeContext
class C_ReserveBehaviorSearch : public C_NodeWrapper<C_ReserveBehaviorSearch, C_Decorator, S_BaseNodeContext>
{
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_ReserveBehaviorSearch) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
