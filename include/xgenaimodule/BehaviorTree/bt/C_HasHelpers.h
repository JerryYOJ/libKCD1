#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Gate.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <HasHelpers>.

namespace wh::xgenaimodule::BehaviorTree {

// <HasHelpers>  RTTI C_HasHelpers  vtable 0x18235e0b8  size 0x68  base C_Gate  ctx S_HasHelpersContext
struct S_HasHelpersContext;
class C_HasHelpers : public C_NodeWrapper<C_HasHelpers, C_Gate, S_HasHelpersContext>
{
    // no own data members (object == 0x68)
};
static_assert(sizeof(C_HasHelpers) == 0x68);

}  // namespace wh::xgenaimodule::BehaviorTree
