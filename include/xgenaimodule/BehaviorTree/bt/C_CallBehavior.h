#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_SmartEntityBehaviorTag.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <CallBehavior>.

namespace wh::xgenaimodule::BehaviorTree {

// <CallBehavior>  RTTI C_CallBehavior  vtable 0x1821c4c38  size 0x38  base C_SmartEntityBehaviorTag  ctx S_CallBehaviorContext
struct S_CallBehaviorContext;
class C_CallBehavior : public C_NodeWrapper<C_CallBehavior, C_SmartEntityBehaviorTag, S_CallBehaviorContext>
{
    uint8_t _ownState[0x10];   // [UNVERIFIED] own members above C_SmartEntityBehaviorTag (0x28)
};
static_assert(sizeof(C_CallBehavior) == 0x38);

}  // namespace wh::xgenaimodule::BehaviorTree
