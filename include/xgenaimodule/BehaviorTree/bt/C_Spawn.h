#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <Spawn>.

namespace wh::xgenaimodule::BehaviorTree {

// <Spawn>  RTTI C_Spawn  vtable 0x182349138  size 0x28  base C_Node  ctx S_SpawnContext
struct S_SpawnContext;
class C_Spawn : public C_NodeWrapper<C_Spawn, C_Node, S_SpawnContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_Spawn) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
