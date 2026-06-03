#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Decorator.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <BehaviorTagCatch>.

namespace wh::xgenaimodule::BehaviorTree {

// <BehaviorTagCatch>  RTTI C_BehaviorTagCatch  vtable 0x1821fb9c8  size 0x38  base C_Decorator  ctx S_BehaviorTagCatchContext
struct S_BehaviorTagCatchContext;
class C_BehaviorTagCatch : public C_NodeWrapper<C_BehaviorTagCatch, C_Decorator, S_BehaviorTagCatchContext>
{
    uint8_t _ownState[0x8];   // [UNVERIFIED] own members above C_Decorator (0x30)
};
static_assert(sizeof(C_BehaviorTagCatch) == 0x38);

}  // namespace wh::xgenaimodule::BehaviorTree
