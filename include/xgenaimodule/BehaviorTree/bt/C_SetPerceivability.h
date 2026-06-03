#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <SetPerceivability>.

namespace wh::xgenaimodule::BehaviorTree {

// <SetPerceivability>  RTTI C_SetPerceivability  vtable 0x18238c960  size 0x28  base C_Node  ctx S_SetPerceivabilityContext
struct S_SetPerceivabilityContext;
class C_SetPerceivability : public C_NodeWrapper<C_SetPerceivability, C_Node, S_SetPerceivabilityContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_SetPerceivability) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
