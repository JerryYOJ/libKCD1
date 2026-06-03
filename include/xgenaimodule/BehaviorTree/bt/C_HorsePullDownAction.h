#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <HorsePullDownAction>.

namespace wh::xgenaimodule::BehaviorTree {

// <HorsePullDownAction>  RTTI C_HorsePullDownAction  vtable 0x182353b18  size 0x28  base C_Node  ctx S_HorsePullDownActionContext
struct S_HorsePullDownActionContext;
class C_HorsePullDownAction : public C_NodeWrapper<C_HorsePullDownAction, C_Node, S_HorsePullDownActionContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_HorsePullDownAction) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
