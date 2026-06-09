#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Decorator.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <TimerBox>.

namespace wh::xgenaimodule::BehaviorTree {

// <TimerBox>  RTTI C_TimerBox  vtable 0x1826f62f8  size 0x40  base C_Decorator  ctx S_TimerBoxContext
struct S_TimerBoxContext;
class C_TimerBox : public C_NodeWrapper<C_TimerBox, C_Decorator, S_TimerBoxContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_TimerBox;
    uint8_t _ownState[0x10];   // [UNVERIFIED] own members above C_Decorator (0x30)
};
static_assert(sizeof(C_TimerBox) == 0x40);

}  // namespace wh::xgenaimodule::BehaviorTree
