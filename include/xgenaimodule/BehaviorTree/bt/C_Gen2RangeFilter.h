#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "C_GraphSearchFilterBase.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <Gen2RangeFilter>.

namespace wh::xgenaimodule::BehaviorTree {

// <Gen2RangeFilter>  RTTI C_Gen2RangeFilter  vtable 0x1826fdb60  size 0x30  base C_GraphSearchFilterBase<C_Gen2RangeFilter, C_Node>  ctx S_Gen2RangeFilterContext
struct S_Gen2RangeFilterContext;
class C_Gen2RangeFilter : public C_NodeWrapper<C_Gen2RangeFilter, C_GraphSearchFilterBase<C_Gen2RangeFilter, C_Node>, S_Gen2RangeFilterContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_Gen2RangeFilter;
    uint8_t _ownState[0x8];   // [UNVERIFIED] own members above C_GraphSearchFilterBase<C_Gen2RangeFilter, C_Node> (0x28)
};
static_assert(sizeof(C_Gen2RangeFilter) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
