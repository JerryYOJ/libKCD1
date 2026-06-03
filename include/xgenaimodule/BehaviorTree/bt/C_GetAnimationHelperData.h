#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <GetAnimationHelperData>.

namespace wh::xgenaimodule::BehaviorTree {

// <GetAnimationHelperData>  RTTI C_GetAnimationHelperData  vtable 0x1823237e8  size 0x28  base C_Node  ctx S_GetAnimationHelperDataContext
struct S_GetAnimationHelperDataContext;
class C_GetAnimationHelperData : public C_NodeWrapper<C_GetAnimationHelperData, C_Node, S_GetAnimationHelperDataContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_GetAnimationHelperData) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
