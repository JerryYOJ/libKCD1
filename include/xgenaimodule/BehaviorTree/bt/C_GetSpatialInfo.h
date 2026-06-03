#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <GetSpatialInfo>.

namespace wh::xgenaimodule::BehaviorTree {

// <GetSpatialInfo>  RTTI C_GetSpatialInfo  vtable 0x182206d48  size 0x28  base C_Node  ctx S_GetSpatialInfoContext
struct S_GetSpatialInfoContext;
class C_GetSpatialInfo : public C_NodeWrapper<C_GetSpatialInfo, C_Node, S_GetSpatialInfoContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_GetSpatialInfo) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
