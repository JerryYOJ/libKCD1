#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Decorator.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <DisableMoveTransitions>.

namespace wh::xgenaimodule::BehaviorTree {

// <DisableMoveTransitions>  RTTI C_DisableMoveTransitions  vtable 0x1821ef748  size 0x30  base C_WrapperDecorator  ctx S_WrapperDecoratorContext
struct S_WrapperDecoratorContext;
class C_DisableMoveTransitions : public C_NodeWrapper<C_DisableMoveTransitions, C_WrapperDecorator, S_WrapperDecoratorContext>
{
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_DisableMoveTransitions) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
