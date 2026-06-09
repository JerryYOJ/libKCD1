#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Decorator.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <PlayerOnBedState>.

namespace wh::xgenaimodule::BehaviorTree {

// <PlayerOnBedState>  RTTI C_PlayerOnBedState  vtable 0x18233e140  size 0x30  base C_Decorator  ctx S_PlayerOnBedStateContext
struct S_PlayerOnBedStateContext;
class C_PlayerOnBedState : public C_NodeWrapper<C_PlayerOnBedState, C_Decorator, S_PlayerOnBedStateContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_PlayerOnBedState;
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_PlayerOnBedState) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
