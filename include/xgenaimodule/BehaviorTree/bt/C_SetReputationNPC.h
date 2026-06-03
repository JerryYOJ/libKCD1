#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <SetReputationNPC>.

namespace wh::xgenaimodule::BehaviorTree {

// <SetReputationNPC>  RTTI C_SetReputationNPC  vtable 0x18234a0e0  size 0x28  base C_Node  ctx S_SetReputationNPCContext
struct S_SetReputationNPCContext;
class C_SetReputationNPC : public C_NodeWrapper<C_SetReputationNPC, C_Node, S_SetReputationNPCContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_SetReputationNPC) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
