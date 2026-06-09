#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_BehaviorAdopter.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <PickUpBehavior>.

namespace wh::xgenaimodule::BehaviorTree {

// <PickUpBehavior>  RTTI C_PickUpBehavior  vtable 0x1826eb3e0  size 0x38  base C_BehaviorAdopter  ctx S_PickUpBehaviorContext
struct S_PickUpBehaviorContext;
class C_PickUpBehavior : public C_NodeWrapper<C_PickUpBehavior, C_BehaviorAdopter, S_PickUpBehaviorContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_PickUpBehavior;
    uint8_t _ownState[0x10];   // [UNVERIFIED] own members above C_BehaviorAdopter (0x28)
};
static_assert(sizeof(C_PickUpBehavior) == 0x38);

}  // namespace wh::xgenaimodule::BehaviorTree
