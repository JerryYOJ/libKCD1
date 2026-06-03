#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <Despawn>.

namespace wh::xgenaimodule::BehaviorTree {

// <Despawn>  RTTI C_Despawn  vtable 0x182223918  size 0x28  base C_Node  ctx S_DespawnContext
struct S_DespawnContext;
class C_Despawn : public C_NodeWrapper<C_Despawn, C_Node, S_DespawnContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_Despawn) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
