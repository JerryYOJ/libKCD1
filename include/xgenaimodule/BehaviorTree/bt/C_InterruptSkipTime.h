#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_DefferedStateChange.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <InterruptSkipTime>.

namespace wh::xgenaimodule::BehaviorTree {

// <InterruptSkipTime>  RTTI C_InterruptSkipTime  vtable 0x182226138  size 0x28  base C_DefferedStateChange  ctx S_InterruptSkipTimeContext
struct S_InterruptSkipTimeContext;
class C_InterruptSkipTime : public C_NodeWrapper<C_InterruptSkipTime, C_DefferedStateChange, S_InterruptSkipTimeContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_InterruptSkipTime) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
