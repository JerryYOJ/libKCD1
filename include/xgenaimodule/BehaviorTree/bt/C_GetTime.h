#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <GetTime>.

namespace wh::xgenaimodule::BehaviorTree {

// <GetTime>  RTTI C_GetTime  vtable 0x182201630  size 0x28  base C_Node  ctx S_GetTimeContext
struct S_GetTimeContext;
class C_GetTime : public C_NodeWrapper<C_GetTime, C_Node, S_GetTimeContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_GetTime;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_GetTime) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
