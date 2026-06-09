#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_DefferedStateChange.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <PlayAnimation>.

namespace wh::xgenaimodule::BehaviorTree {

// <PlayAnimation>  RTTI C_PlayAnimation  vtable 0x1821d39f0  size 0x58  base C_DefferedStateChange  ctx S_PlayAnimationContext
struct S_PlayAnimationContext;
class C_PlayAnimation : public C_NodeWrapper<C_PlayAnimation, C_DefferedStateChange, S_PlayAnimationContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_PlayAnimation;
    uint8_t _ownState[0x30];   // [UNVERIFIED] own members above C_DefferedStateChange (0x28)
};
static_assert(sizeof(C_PlayAnimation) == 0x58);

}  // namespace wh::xgenaimodule::BehaviorTree
