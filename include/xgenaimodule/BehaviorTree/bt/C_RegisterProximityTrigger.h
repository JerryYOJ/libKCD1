#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <RegisterProximityTrigger>.

namespace wh::xgenaimodule::BehaviorTree {

// <RegisterProximityTrigger>  RTTI C_RegisterProximityTrigger  vtable 0x18233b868  size 0x28  base C_Node  ctx S_RegisterProximityTriggerContext
struct S_RegisterProximityTriggerContext;
class C_RegisterProximityTrigger : public C_NodeWrapper<C_RegisterProximityTrigger, C_Node, S_RegisterProximityTriggerContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_RegisterProximityTrigger) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
