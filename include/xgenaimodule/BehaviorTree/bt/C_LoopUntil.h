#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Decorator.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <LoopUntil>.

namespace wh::xgenaimodule::BehaviorTree {

// <LoopUntil>  RTTI C_LoopUntil  vtable 0x1821fffa0  size 0x30  base C_Decorator  ctx S_LoopUntilContext
struct S_LoopUntilContext;
class C_LoopUntil : public C_NodeWrapper<C_LoopUntil, C_Decorator, S_LoopUntilContext>
{
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_LoopUntil) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
