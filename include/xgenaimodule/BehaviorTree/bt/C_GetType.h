#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <GetType>.

namespace wh::xgenaimodule::BehaviorTree {

// <GetType>  RTTI C_GetType  vtable 0x182206678  size 0x28  base C_Node  ctx S_GetTypeContext
struct S_GetTypeContext;
class C_GetType : public C_NodeWrapper<C_GetType, C_Node, S_GetTypeContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_GetType) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
