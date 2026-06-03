#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <ReachTargetCheck>.

namespace wh::xgenaimodule::BehaviorTree {

// <ReachTargetCheck>  RTTI C_ReachTargetCheck  vtable 0x18233cb10  size 0x28  base C_Node  ctx S_ReachTargetCheckContext
struct S_ReachTargetCheckContext;
class C_ReachTargetCheck : public C_NodeWrapper<C_ReachTargetCheck, C_Node, S_ReachTargetCheckContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_ReachTargetCheck) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
