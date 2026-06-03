#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <ClearTemporarySuperfaction>.

namespace wh::xgenaimodule::BehaviorTree {

// <ClearTemporarySuperfaction>  RTTI C_ClearTemporarySuperfaction  vtable 0x182223df8  size 0x28  base C_Node  ctx S_ClearTemporarySuperfactionContext
struct S_ClearTemporarySuperfactionContext;
class C_ClearTemporarySuperfaction : public C_NodeWrapper<C_ClearTemporarySuperfaction, C_Node, S_ClearTemporarySuperfactionContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_ClearTemporarySuperfaction) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
