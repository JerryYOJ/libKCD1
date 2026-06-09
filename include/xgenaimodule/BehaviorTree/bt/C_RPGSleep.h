#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_BuffDecoratorBase.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <RPGSleep>.

namespace wh::xgenaimodule::BehaviorTree {

// <RPGSleep>  RTTI C_RPGSleep  vtable 0x1823566f0  size 0x30  base C_BuffDecoratorBase  ctx S_RPGSleepContext
struct S_RPGSleepContext;
class C_RPGSleep : public C_NodeWrapper<C_RPGSleep, C_BuffDecoratorBase, S_RPGSleepContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_RPGSleep;
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_RPGSleep) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
