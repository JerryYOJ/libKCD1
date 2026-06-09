#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <InterruptFastTravel>.

namespace wh::xgenaimodule::BehaviorTree {

// <InterruptFastTravel>  RTTI C_InterruptFastTravel  vtable 0x1822219d0  size 0x28  base C_Node  ctx S_InterruptFastTravelContext
struct S_InterruptFastTravelContext;
class C_InterruptFastTravel : public C_NodeWrapper<C_InterruptFastTravel, C_Node, S_InterruptFastTravelContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_InterruptFastTravel;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_InterruptFastTravel) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
