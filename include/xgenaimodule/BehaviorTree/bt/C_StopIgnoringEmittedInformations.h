#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <StopIgnoringEmittedInformations>.

namespace wh::xgenaimodule::BehaviorTree {

// <StopIgnoringEmittedInformations>  RTTI C_StopIgnoringEmittedInformations  vtable 0x182374328  size 0x28  base C_Node  ctx S_StopIgnoringEmittedInformationsContext
struct S_StopIgnoringEmittedInformationsContext;
class C_StopIgnoringEmittedInformations : public C_NodeWrapper<C_StopIgnoringEmittedInformations, C_Node, S_StopIgnoringEmittedInformationsContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_StopIgnoringEmittedInformations) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
