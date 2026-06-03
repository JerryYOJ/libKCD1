#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <SetSpatialInfo>.

namespace wh::xgenaimodule::BehaviorTree {

// <SetSpatialInfo>  RTTI C_SetSpatialInfo  vtable 0x18220ee58  size 0x28  base C_Node  ctx S_SetSpatialInfoContext
struct S_SetSpatialInfoContext;
class C_SetSpatialInfo : public C_NodeWrapper<C_SetSpatialInfo, C_Node, S_SetSpatialInfoContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_SetSpatialInfo) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
