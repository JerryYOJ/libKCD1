#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Gate.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <CheckWuidValid>.

namespace wh::xgenaimodule::BehaviorTree {

// <CheckWuidValid>  RTTI C_CheckWuidValid  vtable 0x182215890  size 0x68  base C_Gate  ctx S_CheckWuidValidContext
struct S_CheckWuidValidContext;
class C_CheckWuidValid : public C_NodeWrapper<C_CheckWuidValid, C_Gate, S_CheckWuidValidContext>
{
    // no own data members (object == 0x68)
};
static_assert(sizeof(C_CheckWuidValid) == 0x68);

}  // namespace wh::xgenaimodule::BehaviorTree
