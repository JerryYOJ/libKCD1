#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Decorator.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <AtomicDecorator>.

namespace wh::xgenaimodule::BehaviorTree {

// <AtomicDecorator>  RTTI C_AtomicDecorator  vtable 0x18219d3e0  size 0x30  base C_Decorator  ctx S_BaseNodeContext
class C_AtomicDecorator : public C_NodeWrapper<C_AtomicDecorator, C_Decorator, S_BaseNodeContext>
{
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_AtomicDecorator) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
