#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_MakeIdleBase.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <InstantMakeMeIdle>.

namespace wh::xgenaimodule::BehaviorTree {

// <InstantMakeMeIdle>  RTTI C_InstantMakeMeIdle  vtable 0x18232b5a0  size 0x28  base C_MakeIdleBase  ctx S_InstantMakeMeIdleContext
struct S_InstantMakeMeIdleContext;
class C_InstantMakeMeIdle : public C_NodeWrapper<C_InstantMakeMeIdle, C_MakeIdleBase, S_InstantMakeMeIdleContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_InstantMakeMeIdle) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
