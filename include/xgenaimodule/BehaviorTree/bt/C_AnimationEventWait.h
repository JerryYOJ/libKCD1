#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_DefferedStateChange.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <AnimationEventWait>.

namespace wh::xgenaimodule::BehaviorTree {

// <AnimationEventWait>  RTTI C_AnimationEventWait  vtable 0x1821d3288  size 0x28  base C_DefferedStateChange  ctx S_AnimationEventWaitContext
struct S_AnimationEventWaitContext;
class C_AnimationEventWait : public C_NodeWrapper<C_AnimationEventWait, C_DefferedStateChange, S_AnimationEventWaitContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_AnimationEventWait;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_AnimationEventWait) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
