#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Gate.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <IsLoadedGate>.

namespace wh::xgenaimodule::BehaviorTree {

// <IsLoadedGate>  RTTI C_IsLoadedGate  vtable 0x18235d978  size 0x68  base C_Gate  ctx S_GateContext
struct S_GateContext;
class C_IsLoadedGate : public C_NodeWrapper<C_IsLoadedGate, C_Gate, S_GateContext>
{
    // no own data members (object == 0x68)
};
static_assert(sizeof(C_IsLoadedGate) == 0x68);

}  // namespace wh::xgenaimodule::BehaviorTree
