#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <SetRandomEventsMode>.

namespace wh::xgenaimodule::BehaviorTree {

// <SetRandomEventsMode>  RTTI C_SetRandomEventsMode  vtable 0x18234ac68  size 0x28  base C_Node  ctx S_SetRandomEventsModeContext
struct S_SetRandomEventsModeContext;
class C_SetRandomEventsMode : public C_NodeWrapper<C_SetRandomEventsMode, C_Node, S_SetRandomEventsModeContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_SetRandomEventsMode) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
