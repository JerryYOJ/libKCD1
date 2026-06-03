#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_SweetSpotBounceBase.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <SweetSpotDorsalBounce>.

namespace wh::xgenaimodule::BehaviorTree {

// <SweetSpotDorsalBounce>  RTTI C_SweetSpotDorsalBounce  vtable 0x18236d3f0  size 0x28  base C_SweetSpotBounceBase<C_Node>  ctx S_BaseNodeContext
class C_SweetSpotDorsalBounce : public C_NodeWrapper<C_SweetSpotDorsalBounce, C_SweetSpotBounceBase<C_Node>, S_BaseNodeContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_SweetSpotDorsalBounce) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
