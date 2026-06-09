#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_DefferedStateChange.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <StopAnimation>.

namespace wh::xgenaimodule::BehaviorTree {

// <StopAnimation>  RTTI C_StopAnimation  vtable 0x182348bf8  size 0x28  base C_DefferedStateChange  ctx S_StopAnimationContext
struct S_StopAnimationContext;
class C_StopAnimation : public C_NodeWrapper<C_StopAnimation, C_DefferedStateChange, S_StopAnimationContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_StopAnimation;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_StopAnimation) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
