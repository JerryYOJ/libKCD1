#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <CheckIfPlayerCanSleep>.

namespace wh::xgenaimodule::BehaviorTree {

// <CheckIfPlayerCanSleep>  RTTI C_CheckIfPlayerCanSleep  vtable 0x182389af8  size 0x28  base C_Node  ctx S_CheckIfPlayerCanSleepContext
struct S_CheckIfPlayerCanSleepContext;
class C_CheckIfPlayerCanSleep : public C_NodeWrapper<C_CheckIfPlayerCanSleep, C_Node, S_CheckIfPlayerCanSleepContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_CheckIfPlayerCanSleep;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_CheckIfPlayerCanSleep) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
