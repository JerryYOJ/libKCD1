#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <GetRandomNavmeshPosDebug>.

namespace wh::xgenaimodule::BehaviorTree {

// <GetRandomNavmeshPosDebug>  RTTI C_GetRandomNavmeshPosDebug  vtable 0x18232c4b8  size 0x28  base C_Node  ctx S_GetRandomNavmeshPosDebugContext
struct S_GetRandomNavmeshPosDebugContext;
class C_GetRandomNavmeshPosDebug : public C_NodeWrapper<C_GetRandomNavmeshPosDebug, C_Node, S_GetRandomNavmeshPosDebugContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_GetRandomNavmeshPosDebug) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
