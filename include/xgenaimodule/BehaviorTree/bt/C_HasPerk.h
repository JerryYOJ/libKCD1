#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <HasPerk>.

namespace wh::xgenaimodule::BehaviorTree {

// <HasPerk>  RTTI C_HasPerk  vtable 0x182387ed8  size 0x28  base C_Node  ctx S_HasPerkContext
struct S_HasPerkContext;
class C_HasPerk : public C_NodeWrapper<C_HasPerk, C_Node, S_HasPerkContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_HasPerk) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
