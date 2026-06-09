#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Barrier.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <FollowTarget>.

namespace wh::xgenaimodule::BehaviorTree {

// <FollowTarget>  RTTI C_FollowTarget  vtable 0x18236f040  size 0x30  base C_PassiveBarrier  ctx S_FollowTargetContext
struct S_FollowTargetContext;
class C_FollowTarget : public C_NodeWrapper<C_FollowTarget, C_PassiveBarrier, S_FollowTargetContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_FollowTarget;
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_FollowTarget) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
