#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Barrier.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <EnsureWuidValid>.

namespace wh::xgenaimodule::BehaviorTree {

// <EnsureWuidValid>  RTTI C_EnsureWuidValid  vtable 0x182223420  size 0x30  base C_PassiveBarrier  ctx S_EnsureWuidValidContext
struct S_EnsureWuidValidContext;
class C_EnsureWuidValid : public C_NodeWrapper<C_EnsureWuidValid, C_PassiveBarrier, S_EnsureWuidValidContext>
{
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_EnsureWuidValid) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
