#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_LockNode.h"
#include "../C_Decorator.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <InstantSemaphore>.

namespace wh::xgenaimodule::BehaviorTree {

// <InstantSemaphore>  RTTI C_InstantSemaphore  vtable 0x1821f0028  size 0x30  base C_LockNode<C_Decorator>  ctx S_InstantSemaphoreContext
struct S_InstantSemaphoreContext;
class C_InstantSemaphore : public C_NodeWrapper<C_InstantSemaphore, C_LockNode<C_Decorator>, S_InstantSemaphoreContext>
{
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_InstantSemaphore) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
