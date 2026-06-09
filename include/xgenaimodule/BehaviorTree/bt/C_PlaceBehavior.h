#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_BehaviorAdopter.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <PlaceBehavior>.

namespace wh::xgenaimodule::BehaviorTree {

// <PlaceBehavior>  RTTI C_PlaceBehavior  vtable 0x1826ed440  size 0x38  base C_BehaviorAdopter  ctx S_PlaceBehaviorContext
struct S_PlaceBehaviorContext;
class C_PlaceBehavior : public C_NodeWrapper<C_PlaceBehavior, C_BehaviorAdopter, S_PlaceBehaviorContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_PlaceBehavior;
    uint8_t _ownState[0x10];   // [UNVERIFIED] own members above C_BehaviorAdopter (0x28)
};
static_assert(sizeof(C_PlaceBehavior) == 0x38);

}  // namespace wh::xgenaimodule::BehaviorTree
