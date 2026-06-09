#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <SetFollowTarget>.

namespace wh::xgenaimodule::BehaviorTree {

// <SetFollowTarget>  RTTI C_SetFollowTarget  vtable 0x18236e4a0  size 0x28  base C_Node  ctx S_SetFollowTargetContext
struct S_SetFollowTargetContext;
class C_SetFollowTarget : public C_NodeWrapper<C_SetFollowTarget, C_Node, S_SetFollowTargetContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_SetFollowTarget;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_SetFollowTarget) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
