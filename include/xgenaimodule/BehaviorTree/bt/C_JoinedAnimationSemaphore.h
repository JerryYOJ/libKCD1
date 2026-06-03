#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_Semaphore.h"
#include "C_JoinedAnimationLockBase.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <JoinedAnimationSemaphore>.

namespace wh::xgenaimodule::BehaviorTree {

// <JoinedAnimationSemaphore>  RTTI C_JoinedAnimationSemaphore  vtable 0x182380398  size 0x30  base C_JoinedAnimationLockBase<C_Semaphore>  ctx S_BaseNodeContext
class C_JoinedAnimationSemaphore : public C_NodeWrapper<C_JoinedAnimationSemaphore, C_JoinedAnimationLockBase<C_Semaphore>, S_BaseNodeContext>
{
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_JoinedAnimationSemaphore) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
