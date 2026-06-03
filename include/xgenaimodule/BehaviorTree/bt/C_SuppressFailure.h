#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Decorator.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <SuppressFailure>.

namespace wh::xgenaimodule::BehaviorTree {

// <SuppressFailure>  RTTI C_SuppressFailure  vtable 0x1821f1b90  size 0x30  base C_Decorator  ctx S_BaseNodeContext
class C_SuppressFailure : public C_NodeWrapper<C_SuppressFailure, C_Decorator, S_BaseNodeContext>
{
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_SuppressFailure) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
