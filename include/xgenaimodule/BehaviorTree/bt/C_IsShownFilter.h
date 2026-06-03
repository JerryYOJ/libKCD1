#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_LinkFilterWithSource.h"
#include "../C_Node.h"
#include "C_LinkLimitedData.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <IsShownFilter>.

namespace wh::xgenaimodule::BehaviorTree {

// <IsShownFilter>  RTTI C_IsShownFilter  vtable 0x1826ff8f0  size 0x30  base C_LinkFilterWithSource<C_IsShownFilter, C_LinkLimitedData<C_Node>>  ctx S_BaseNodeContext
class C_IsShownFilter : public C_NodeWrapper<C_IsShownFilter, C_LinkFilterWithSource<C_IsShownFilter, C_LinkLimitedData<C_Node>>, S_BaseNodeContext>
{
    uint8_t _ownState[0x8];   // [UNVERIFIED] own members above C_LinkFilterWithSource<C_IsShownFilter, C_LinkLimitedData<C_Node>> (0x28)
};
static_assert(sizeof(C_IsShownFilter) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
