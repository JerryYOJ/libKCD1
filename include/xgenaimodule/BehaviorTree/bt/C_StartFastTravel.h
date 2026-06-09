#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <StartFastTravel>.

namespace wh::xgenaimodule::BehaviorTree {

// <StartFastTravel>  RTTI C_StartFastTravel  vtable 0x18233dbf8  size 0x28  base C_Node  ctx S_StartFastTravelContext
struct S_StartFastTravelContext;
class C_StartFastTravel : public C_NodeWrapper<C_StartFastTravel, C_Node, S_StartFastTravelContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_StartFastTravel;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_StartFastTravel) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
