#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_GraphSearchFilterBase.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <Gen2WUIDFilter>.

namespace wh::xgenaimodule::BehaviorTree {

// <Gen2WUIDFilter>  RTTI C_Gen2WUIDFilter  vtable 0x1826fd0a0  size 0x30  base C_GraphSearchFilterBase<C_Gen2WUIDFilter, C_Node>  ctx S_Gen2WUIDFilterContext
struct S_Gen2WUIDFilterContext;
class C_Gen2WUIDFilter : public C_NodeWrapper<C_Gen2WUIDFilter, C_GraphSearchFilterBase<C_Gen2WUIDFilter, C_Node>, S_Gen2WUIDFilterContext>
{
    uint8_t _ownState[0x8];   // [UNVERIFIED] own members above C_GraphSearchFilterBase<C_Gen2WUIDFilter, C_Node> (0x28)
};
static_assert(sizeof(C_Gen2WUIDFilter) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
