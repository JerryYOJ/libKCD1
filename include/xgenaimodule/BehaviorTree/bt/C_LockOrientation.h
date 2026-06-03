#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Decorator.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <LockOrientation>.

namespace wh::xgenaimodule::BehaviorTree {

// <LockOrientation>  RTTI C_LockOrientation  vtable 0x182366148  size 0x30  base C_WrapperDecorator  ctx S_LockOrientationContext
struct S_LockOrientationContext;
class C_LockOrientation : public C_NodeWrapper<C_LockOrientation, C_WrapperDecorator, S_LockOrientationContext>
{
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_LockOrientation) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
