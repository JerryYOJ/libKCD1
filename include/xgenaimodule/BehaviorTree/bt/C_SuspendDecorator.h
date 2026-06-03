#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Decorator.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <SuspendDecorator>.

namespace wh::xgenaimodule::BehaviorTree {

// <SuspendDecorator>  RTTI C_SuspendDecorator  vtable 0x182363cb0  size 0x30  base C_Decorator  ctx S_SuspendDecoratorContext
struct S_SuspendDecoratorContext;
class C_SuspendDecorator : public C_NodeWrapper<C_SuspendDecorator, C_Decorator, S_SuspendDecoratorContext>
{
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_SuspendDecorator) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
