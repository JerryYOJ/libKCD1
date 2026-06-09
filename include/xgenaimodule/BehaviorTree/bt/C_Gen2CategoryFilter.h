#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_GraphSearchFilterBase.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <Gen2CategoryFilter>.

namespace wh::xgenaimodule::BehaviorTree {

// <Gen2CategoryFilter>  RTTI C_Gen2CategoryFilter  vtable 0x1826fddb8  size 0x30  base C_GraphSearchFilterBase<C_Gen2CategoryFilter, C_Node>  ctx S_Gen2CategoryFilterContext
struct S_Gen2CategoryFilterContext;
class C_Gen2CategoryFilter : public C_NodeWrapper<C_Gen2CategoryFilter, C_GraphSearchFilterBase<C_Gen2CategoryFilter, C_Node>, S_Gen2CategoryFilterContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_Gen2CategoryFilter;
    uint8_t _ownState[0x8];   // [UNVERIFIED] own members above C_GraphSearchFilterBase<C_Gen2CategoryFilter, C_Node> (0x28)
};
static_assert(sizeof(C_Gen2CategoryFilter) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
