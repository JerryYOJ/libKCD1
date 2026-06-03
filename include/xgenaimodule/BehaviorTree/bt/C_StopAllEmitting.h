#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <StopAllEmitting>.

namespace wh::xgenaimodule::BehaviorTree {

// <StopAllEmitting>  RTTI C_StopAllEmitting  vtable 0x182374660  size 0x28  base C_Node  ctx S_StopAllEmittingContext
struct S_StopAllEmittingContext;
class C_StopAllEmitting : public C_NodeWrapper<C_StopAllEmitting, C_Node, S_StopAllEmittingContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_StopAllEmitting) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
