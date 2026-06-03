#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <SetReputationFaction>.

namespace wh::xgenaimodule::BehaviorTree {

// <SetReputationFaction>  RTTI C_SetReputationFaction  vtable 0x18234a650  size 0x28  base C_Node  ctx S_SetReputationFactionContext
struct S_SetReputationFactionContext;
class C_SetReputationFaction : public C_NodeWrapper<C_SetReputationFaction, C_Node, S_SetReputationFactionContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_SetReputationFaction) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
