#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_LinkFilterWithSource.h"
#include "../C_Node.h"
#include "C_LinkLimitedData.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <HasBehaviorFilter>.

namespace wh::xgenaimodule::BehaviorTree {

// <HasBehaviorFilter>  RTTI C_HasBehaviorFilter  vtable 0x1821de3e8  size 0x30  base C_LinkFilterWithSource<C_HasBehaviorFilter, C_LinkLimitedData<C_Node>>  ctx S_BaseNodeContext
class C_HasBehaviorFilter : public C_NodeWrapper<C_HasBehaviorFilter, C_LinkFilterWithSource<C_HasBehaviorFilter, C_LinkLimitedData<C_Node>>, S_BaseNodeContext>
{
    uint8_t _ownState[0x8];   // [UNVERIFIED] own members above C_LinkFilterWithSource<C_HasBehaviorFilter, C_LinkLimitedData<C_Node>> (0x28)
};
static_assert(sizeof(C_HasBehaviorFilter) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
