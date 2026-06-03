#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <SetGlobalVar>.

namespace wh::xgenaimodule::BehaviorTree {

// <SetGlobalVar>  RTTI C_SetGlobalVar  vtable 0x18233a368  size 0x28  base C_Node  ctx S_SetGlobalVarContext
struct S_SetGlobalVarContext;
class C_SetGlobalVar : public C_NodeWrapper<C_SetGlobalVar, C_Node, S_SetGlobalVarContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_SetGlobalVar) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
