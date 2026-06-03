#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <RemoveBuffs>.

namespace wh::xgenaimodule::BehaviorTree {

// <RemoveBuffs>  RTTI C_RemoveBuffs  vtable 0x182214d48  size 0x28  base C_Node  ctx S_RemoveBuffsContext
struct S_RemoveBuffsContext;
class C_RemoveBuffs : public C_NodeWrapper<C_RemoveBuffs, C_Node, S_RemoveBuffsContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_RemoveBuffs) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
