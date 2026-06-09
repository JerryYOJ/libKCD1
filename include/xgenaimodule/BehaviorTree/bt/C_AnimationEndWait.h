#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_DefferedStateChange.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <AnimationEndWait>.

namespace wh::xgenaimodule::BehaviorTree {

// <AnimationEndWait>  RTTI C_AnimationEndWait  vtable 0x1821d3010  size 0x28  base C_DefferedStateChange  ctx S_AnimationEndWaitContext
struct S_AnimationEndWaitContext;
class C_AnimationEndWait : public C_NodeWrapper<C_AnimationEndWait, C_DefferedStateChange, S_AnimationEndWaitContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_AnimationEndWait;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_AnimationEndWait) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
