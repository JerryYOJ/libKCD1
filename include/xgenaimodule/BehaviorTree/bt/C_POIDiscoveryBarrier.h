#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Barrier.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <POIDiscoveryBarrier>.

namespace wh::xgenaimodule::BehaviorTree {

// <POIDiscoveryBarrier>  RTTI C_POIDiscoveryBarrier  vtable 0x182365440  size 0x30  base C_PassiveBarrier  ctx S_POIDiscoveryBarrier
struct S_POIDiscoveryBarrier;
class C_POIDiscoveryBarrier : public C_NodeWrapper<C_POIDiscoveryBarrier, C_PassiveBarrier, S_POIDiscoveryBarrier>
{
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_POIDiscoveryBarrier) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
