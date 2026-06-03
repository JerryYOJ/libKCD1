#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Barrier.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <SoulLevelsChangeGate>.

namespace wh::xgenaimodule::BehaviorTree {

// <SoulLevelsChangeGate>  RTTI C_SoulLevelsChangeGate  vtable 0x182393f08  size 0x30  base C_PassiveBarrier  ctx C_SoulLevelsChangeGateContext
struct C_SoulLevelsChangeGateContext;
class C_SoulLevelsChangeGate : public C_NodeWrapper<C_SoulLevelsChangeGate, C_PassiveBarrier, C_SoulLevelsChangeGateContext>
{
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_SoulLevelsChangeGate) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
