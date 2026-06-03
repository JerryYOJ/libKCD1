#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_SuspendDecorator.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <SuspendDecoratorPassive>.

namespace wh::xgenaimodule::BehaviorTree {

// <SuspendDecoratorPassive>  RTTI C_SuspendDecoratorPassive  vtable 0x1823642b8  size 0x30  base C_SuspendDecorator  ctx S_SuspendDecoratorContext
struct S_SuspendDecoratorContext;
class C_SuspendDecoratorPassive : public C_NodeWrapper<C_SuspendDecoratorPassive, C_SuspendDecorator, S_SuspendDecoratorContext>
{
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_SuspendDecoratorPassive) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
