#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Composites.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <SweetSpotFollower>.

namespace wh::xgenaimodule::BehaviorTree {

// <SweetSpotFollower>  RTTI C_SweetSpotFollower  vtable 0x18219c540  size 0x40  base C_Parallel  ctx S_SweetSpotFollowerContext
struct S_SweetSpotFollowerContext;
class C_SweetSpotFollower : public C_NodeWrapper<C_SweetSpotFollower, C_Parallel, S_SweetSpotFollowerContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_SweetSpotFollower;
    // no own data members (object == 0x40)
};
static_assert(sizeof(C_SweetSpotFollower) == 0x40);

}  // namespace wh::xgenaimodule::BehaviorTree
