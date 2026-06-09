#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <RPGSweetSpotArcDriver>.

namespace wh::xgenaimodule::BehaviorTree {

// <RPGSweetSpotArcDriver>  RTTI C_RPGSweetSpotArcDriver  vtable 0x182225778  size 0x28  base C_Node  ctx S_BaseNodeContext
class C_RPGSweetSpotArcDriver : public C_NodeWrapper<C_RPGSweetSpotArcDriver, C_Node, S_BaseNodeContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_RPGSweetSpotArcDriver;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_RPGSweetSpotArcDriver) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
