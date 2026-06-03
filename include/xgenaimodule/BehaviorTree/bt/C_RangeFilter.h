#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_LinkFilterWithSource.h"
#include "../C_Node.h"
#include "C_LinkLimitedData.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <RangeFilter>.

namespace wh::xgenaimodule::BehaviorTree {

// <RangeFilter>  RTTI C_RangeFilter  vtable 0x1821fddf0  size 0x30  base C_LinkFilterWithSource<C_RangeFilter, C_LinkLimitedData<C_Node>>  ctx S_RangeFilterContext
struct S_RangeFilterContext;
class C_RangeFilter : public C_NodeWrapper<C_RangeFilter, C_LinkFilterWithSource<C_RangeFilter, C_LinkLimitedData<C_Node>>, S_RangeFilterContext>
{
    uint8_t _ownState[0x8];   // [UNVERIFIED] own members above C_LinkFilterWithSource<C_RangeFilter, C_LinkLimitedData<C_Node>> (0x28)
};
static_assert(sizeof(C_RangeFilter) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
