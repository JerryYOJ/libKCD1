#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <GetHelperUserData>.

namespace wh::xgenaimodule::BehaviorTree {

// <GetHelperUserData>  RTTI C_GetHelperUserData  vtable 0x182322800  size 0x28  base C_Node  ctx S_GetHelperUserDataContext
struct S_GetHelperUserDataContext;
class C_GetHelperUserData : public C_NodeWrapper<C_GetHelperUserData, C_Node, S_GetHelperUserDataContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_GetHelperUserData) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
