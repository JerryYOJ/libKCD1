#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <InformationEmittingStart>.

namespace wh::xgenaimodule::BehaviorTree {

// <InformationEmittingStart>  RTTI C_InformationEmittingStart  vtable 0x18221e7e0  size 0x28  base C_Node  ctx S_InformationEmittingStartContext
struct S_InformationEmittingStartContext;
class C_InformationEmittingStart : public C_NodeWrapper<C_InformationEmittingStart, C_Node, S_InformationEmittingStartContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_InformationEmittingStart) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
