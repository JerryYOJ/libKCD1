#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <IgnoreEmittedInformations>.

namespace wh::xgenaimodule::BehaviorTree {

// <IgnoreEmittedInformations>  RTTI C_IgnoreEmittedInformations  vtable 0x182375e30  size 0x28  base C_Node  ctx S_IgnoreEmittedInformationsContext
struct S_IgnoreEmittedInformationsContext;
class C_IgnoreEmittedInformations : public C_NodeWrapper<C_IgnoreEmittedInformations, C_Node, S_IgnoreEmittedInformationsContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_IgnoreEmittedInformations) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
