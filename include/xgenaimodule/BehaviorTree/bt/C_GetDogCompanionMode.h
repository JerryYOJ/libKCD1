#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <GetDogCompanionMode>.

namespace wh::xgenaimodule::BehaviorTree {

// <GetDogCompanionMode>  RTTI C_GetDogCompanionMode  vtable 0x1823261f0  size 0x28  base C_Node  ctx S_GetDogCompanionModeContext
struct S_GetDogCompanionModeContext;
class C_GetDogCompanionMode : public C_NodeWrapper<C_GetDogCompanionMode, C_Node, S_GetDogCompanionModeContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_GetDogCompanionMode) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
