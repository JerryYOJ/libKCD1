#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_GraphSearchFilterBase.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <Gen2SoulFactionFilter>.

namespace wh::xgenaimodule::BehaviorTree {

// <Gen2SoulFactionFilter>  RTTI C_Gen2SoulFactionFilter  vtable 0x1826fd498  size 0x30  base C_GraphSearchFilterBase<C_Gen2SoulFactionFilter, C_Node>  ctx S_Gen2SoulFactionFilterContext
struct S_Gen2SoulFactionFilterContext;
class C_Gen2SoulFactionFilter : public C_NodeWrapper<C_Gen2SoulFactionFilter, C_GraphSearchFilterBase<C_Gen2SoulFactionFilter, C_Node>, S_Gen2SoulFactionFilterContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_Gen2SoulFactionFilter;
    uint8_t _ownState[0x8];   // [UNVERIFIED] own members above C_GraphSearchFilterBase<C_Gen2SoulFactionFilter, C_Node> (0x28)
};
static_assert(sizeof(C_Gen2SoulFactionFilter) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
