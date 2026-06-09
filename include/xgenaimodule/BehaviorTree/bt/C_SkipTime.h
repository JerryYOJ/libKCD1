#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_DefferedStateChange.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <SkipTime>.

namespace wh::xgenaimodule::BehaviorTree {

// <SkipTime>  RTTI C_SkipTime  vtable 0x18233cbd8  size 0x28  base C_DefferedStateChange  ctx S_SkipTimeContext
struct S_SkipTimeContext;
class C_SkipTime : public C_NodeWrapper<C_SkipTime, C_DefferedStateChange, S_SkipTimeContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_SkipTime;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_SkipTime) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
