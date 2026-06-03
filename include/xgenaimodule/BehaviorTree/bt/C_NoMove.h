#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Decorator.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <NoMove>.

namespace wh::xgenaimodule::BehaviorTree {

// <NoMove>  RTTI C_NoMove  vtable 0x182365e30  size 0x30  base C_WrapperDecorator  ctx S_WrapperDecoratorContext
struct S_WrapperDecoratorContext;
class C_NoMove : public C_NodeWrapper<C_NoMove, C_WrapperDecorator, S_WrapperDecoratorContext>
{
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_NoMove) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
