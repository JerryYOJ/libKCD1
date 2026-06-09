#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_LinkFilterWithSource.h"
#include "../C_Node.h"
#include "C_LinkLimitedData.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <SoulFactionFilter>.

namespace wh::xgenaimodule::BehaviorTree {

// <SoulFactionFilter>  RTTI C_SoulFactionFilter  vtable 0x1826fe718  size 0x30  base C_LinkFilterWithSource<C_SoulFactionFilter, C_LinkLimitedData<C_Node>>  ctx S_SoulFactionFilterContext
struct S_SoulFactionFilterContext;
class C_SoulFactionFilter : public C_NodeWrapper<C_SoulFactionFilter, C_LinkFilterWithSource<C_SoulFactionFilter, C_LinkLimitedData<C_Node>>, S_SoulFactionFilterContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_SoulFactionFilter;
    uint8_t _ownState[0x8];   // [UNVERIFIED] own members above C_LinkFilterWithSource<C_SoulFactionFilter, C_LinkLimitedData<C_Node>> (0x28)
};
static_assert(sizeof(C_SoulFactionFilter) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
