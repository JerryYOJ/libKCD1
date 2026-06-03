#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <SetWhistling>.

namespace wh::xgenaimodule::BehaviorTree {

// <SetWhistling>  RTTI C_SetWhistling  vtable 0x182349438  size 0x28  base C_Node  ctx S_SetWhistlingContext
struct S_SetWhistlingContext;
class C_SetWhistling : public C_NodeWrapper<C_SetWhistling, C_Node, S_SetWhistlingContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_SetWhistling) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
