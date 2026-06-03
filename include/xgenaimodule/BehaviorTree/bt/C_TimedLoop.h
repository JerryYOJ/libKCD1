#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Composites.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <TimedLoop>.

namespace wh::xgenaimodule::BehaviorTree {

// <TimedLoop>  RTTI C_TimedLoop  vtable 0x182365bc0  size 0x30  base C_Loop  ctx S_TimedLoopContext
struct S_TimedLoopContext;
class C_TimedLoop : public C_NodeWrapper<C_TimedLoop, C_Loop, S_TimedLoopContext>
{
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_TimedLoop) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
