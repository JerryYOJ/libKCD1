#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Gate.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <RandomGate>.

namespace wh::xgenaimodule::BehaviorTree {

// <RandomGate>  RTTI C_RandomGate  vtable 0x182218018  size 0x68  base C_Gate  ctx S_RandomGateContext
struct S_RandomGateContext;
class C_RandomGate : public C_NodeWrapper<C_RandomGate, C_Gate, S_RandomGateContext>
{
    // no own data members (object == 0x68)
};
static_assert(sizeof(C_RandomGate) == 0x68);

}  // namespace wh::xgenaimodule::BehaviorTree
