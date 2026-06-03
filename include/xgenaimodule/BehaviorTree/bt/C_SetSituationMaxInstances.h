#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <SetSituationMaxInstances>.

namespace wh::xgenaimodule::BehaviorTree {

// <SetSituationMaxInstances>  RTTI C_SetSituationMaxInstances  vtable 0x1823917a8  size 0x28  base C_Node  ctx S_SetSituationMaxInstancesContext
struct S_SetSituationMaxInstancesContext;
class C_SetSituationMaxInstances : public C_NodeWrapper<C_SetSituationMaxInstances, C_Node, S_SetSituationMaxInstancesContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_SetSituationMaxInstances) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
