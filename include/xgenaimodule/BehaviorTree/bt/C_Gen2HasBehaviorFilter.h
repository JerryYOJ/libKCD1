#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_GraphSearchFilterBase.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <Gen2HasBehaviorFilter>.

namespace wh::xgenaimodule::BehaviorTree {

// <Gen2HasBehaviorFilter>  RTTI C_Gen2HasBehaviorFilter  vtable 0x1826fd838  size 0x30  base C_GraphSearchFilterBase<C_Gen2HasBehaviorFilter, C_Node>  ctx S_BaseNodeContext
class C_Gen2HasBehaviorFilter : public C_NodeWrapper<C_Gen2HasBehaviorFilter, C_GraphSearchFilterBase<C_Gen2HasBehaviorFilter, C_Node>, S_BaseNodeContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_Gen2HasBehaviorFilter;
    uint8_t _ownState[0x8];   // [UNVERIFIED] own members above C_GraphSearchFilterBase<C_Gen2HasBehaviorFilter, C_Node> (0x28)
};
static_assert(sizeof(C_Gen2HasBehaviorFilter) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
