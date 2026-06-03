#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_SweetSpotBounceBase.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <SweetSpotLateralBounce>.

namespace wh::xgenaimodule::BehaviorTree {

// <SweetSpotLateralBounce>  RTTI C_SweetSpotLateralBounce  vtable 0x18236d020  size 0x28  base C_SweetSpotBounceBase<C_Node>  ctx S_BaseNodeContext
class C_SweetSpotLateralBounce : public C_NodeWrapper<C_SweetSpotLateralBounce, C_SweetSpotBounceBase<C_Node>, S_BaseNodeContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_SweetSpotLateralBounce) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
