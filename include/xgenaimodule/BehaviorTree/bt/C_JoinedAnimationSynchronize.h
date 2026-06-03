#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_JoinedAnimationLockBase.h"
#include "C_Synchronize.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <JoinedAnimationSynchronize>.

namespace wh::xgenaimodule::BehaviorTree {

// <JoinedAnimationSynchronize>  RTTI C_JoinedAnimationSynchronize  vtable 0x182380750  size 0x30  base C_JoinedAnimationLockBase<C_Synchronize>  ctx S_BaseNodeContext
class C_JoinedAnimationSynchronize : public C_NodeWrapper<C_JoinedAnimationSynchronize, C_JoinedAnimationLockBase<C_Synchronize>, S_BaseNodeContext>
{
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_JoinedAnimationSynchronize) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
