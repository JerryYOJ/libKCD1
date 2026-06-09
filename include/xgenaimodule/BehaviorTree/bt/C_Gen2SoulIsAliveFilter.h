#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_GraphSearchFilterBase.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <Gen2SoulIsAliveFilter>.

namespace wh::xgenaimodule::BehaviorTree {

// <Gen2SoulIsAliveFilter>  RTTI C_Gen2SoulIsAliveFilter  vtable 0x1826fcd78  size 0x30  base C_GraphSearchFilterBase<C_Gen2SoulIsAliveFilter, C_Node>  ctx S_Gen2SoulIsAliveFilterContext
struct S_Gen2SoulIsAliveFilterContext;
class C_Gen2SoulIsAliveFilter : public C_NodeWrapper<C_Gen2SoulIsAliveFilter, C_GraphSearchFilterBase<C_Gen2SoulIsAliveFilter, C_Node>, S_Gen2SoulIsAliveFilterContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_Gen2SoulIsAliveFilter;
    uint8_t _ownState[0x8];   // [UNVERIFIED] own members above C_GraphSearchFilterBase<C_Gen2SoulIsAliveFilter, C_Node> (0x28)
};
static_assert(sizeof(C_Gen2SoulIsAliveFilter) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
