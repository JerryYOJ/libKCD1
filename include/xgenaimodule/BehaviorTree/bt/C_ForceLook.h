#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Decorator.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <ForceLook>.

namespace wh::xgenaimodule::BehaviorTree {

// <ForceLook>  RTTI C_ForceLook  vtable 0x1821ec718  size 0x30  base C_WrapperDecorator  ctx S_ForceLookContext
struct S_ForceLookContext;
class C_ForceLook : public C_NodeWrapper<C_ForceLook, C_WrapperDecorator, S_ForceLookContext>
{
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_ForceLook) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
