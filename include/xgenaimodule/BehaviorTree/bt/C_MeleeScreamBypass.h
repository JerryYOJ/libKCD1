#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Decorator.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <MeleeScreamBypass>.

namespace wh::xgenaimodule::BehaviorTree {

// <MeleeScreamBypass>  RTTI C_MeleeScreamBypass  vtable 0x182353380  size 0x30  base C_WrapperDecorator  ctx S_WrapperDecoratorContext
struct S_WrapperDecoratorContext;
class C_MeleeScreamBypass : public C_NodeWrapper<C_MeleeScreamBypass, C_WrapperDecorator, S_WrapperDecoratorContext>
{
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_MeleeScreamBypass) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
