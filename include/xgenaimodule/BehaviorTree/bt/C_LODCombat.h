#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_CombatNode.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <LODCombat>.

namespace wh::xgenaimodule::BehaviorTree {

// <LODCombat>  RTTI C_LODCombat  vtable 0x1821f6a30  size 0x28  base C_CombatNode<C_Node>  ctx S_BaseNodeContext
class C_LODCombat : public C_NodeWrapper<C_LODCombat, C_CombatNode<C_Node>, S_BaseNodeContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_LODCombat) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
