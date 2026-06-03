#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Gate.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <HasTimeRespawnEnabled>.

namespace wh::xgenaimodule::BehaviorTree {

// <HasTimeRespawnEnabled>  RTTI C_HasTimeRespawnEnabled  vtable 0x18235dda8  size 0x68  base C_Gate  ctx S_HasTimeRespawnEnabledContext
struct S_HasTimeRespawnEnabledContext;
class C_HasTimeRespawnEnabled : public C_NodeWrapper<C_HasTimeRespawnEnabled, C_Gate, S_HasTimeRespawnEnabledContext>
{
    // no own data members (object == 0x68)
};
static_assert(sizeof(C_HasTimeRespawnEnabled) == 0x68);

}  // namespace wh::xgenaimodule::BehaviorTree
