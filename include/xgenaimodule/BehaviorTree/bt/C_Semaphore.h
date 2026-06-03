#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_LockBarrier.h"
#include "../C_Decorator.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <Semaphore>.

namespace wh::xgenaimodule::BehaviorTree {

// <Semaphore>  RTTI C_Semaphore  vtable 0x1821f0558  size 0x30  base C_LockBarrier<C_Decorator>  ctx S_SemaphoreContext
struct S_SemaphoreContext;
class C_Semaphore : public C_NodeWrapper<C_Semaphore, C_LockBarrier<C_Decorator>, S_SemaphoreContext>
{
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_Semaphore) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
