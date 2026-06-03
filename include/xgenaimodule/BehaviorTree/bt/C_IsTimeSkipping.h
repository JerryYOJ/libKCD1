#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Gate.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <IsTimeSkipping>.

namespace wh::xgenaimodule::BehaviorTree {

// <IsTimeSkipping>  RTTI C_IsTimeSkipping  vtable 0x18235c640  size 0x68  base C_Gate  ctx S_GateContext
struct S_GateContext;
class C_IsTimeSkipping : public C_NodeWrapper<C_IsTimeSkipping, C_Gate, S_GateContext>
{
    // no own data members (object == 0x68)
};
static_assert(sizeof(C_IsTimeSkipping) == 0x68);

}  // namespace wh::xgenaimodule::BehaviorTree
