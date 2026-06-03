#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_MakeIdleBase.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <MakeMeIdle>.

namespace wh::xgenaimodule::BehaviorTree {

// <MakeMeIdle>  RTTI C_MakeMeIdle  vtable 0x182201d00  size 0x28  base C_MakeIdleBase  ctx S_MakeMeIdleContext
struct S_MakeMeIdleContext;
class C_MakeMeIdle : public C_NodeWrapper<C_MakeMeIdle, C_MakeIdleBase, S_MakeMeIdleContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_MakeMeIdle) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
