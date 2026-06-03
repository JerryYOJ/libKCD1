#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Decorator.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <OnInventoryEvent>.

namespace wh::xgenaimodule::BehaviorTree {

// <OnInventoryEvent>  RTTI C_OnInventoryEvent  vtable 0x1823657a0  size 0x30  base C_Decorator  ctx S_OnInventoryEventContext
struct S_OnInventoryEventContext;
class C_OnInventoryEvent : public C_NodeWrapper<C_OnInventoryEvent, C_Decorator, S_OnInventoryEventContext>
{
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_OnInventoryEvent) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
