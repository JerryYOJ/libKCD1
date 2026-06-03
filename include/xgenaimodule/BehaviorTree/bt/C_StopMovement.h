#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_DefferedStateChange.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <StopMovement>.

namespace wh::xgenaimodule::BehaviorTree {

// <StopMovement>  RTTI C_StopMovement  vtable 0x1823488f0  size 0x28  base C_DefferedStateChange  ctx S_StopMovementContext
struct S_StopMovementContext;
class C_StopMovement : public C_NodeWrapper<C_StopMovement, C_DefferedStateChange, S_StopMovementContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_StopMovement) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
