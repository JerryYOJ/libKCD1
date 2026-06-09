#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Decorator.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <PlayerSleep>.

namespace wh::xgenaimodule::BehaviorTree {

// <PlayerSleep>  RTTI C_PlayerSleep  vtable 0x18233cf18  size 0x30  base C_Decorator  ctx S_PlayerSleepContext
struct S_PlayerSleepContext;
class C_PlayerSleep : public C_NodeWrapper<C_PlayerSleep, C_Decorator, S_PlayerSleepContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_PlayerSleep;
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_PlayerSleep) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
