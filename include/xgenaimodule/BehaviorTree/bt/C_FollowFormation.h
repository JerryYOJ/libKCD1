#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Barrier.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <FollowFormation>.

namespace wh::xgenaimodule::BehaviorTree {

// <FollowFormation>  RTTI C_FollowFormation  vtable 0x18236fc00  size 0x30  base C_PassiveBarrier  ctx S_FollowFormationContext
struct S_FollowFormationContext;
class C_FollowFormation : public C_NodeWrapper<C_FollowFormation, C_PassiveBarrier, S_FollowFormationContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_FollowFormation;
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_FollowFormation) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
