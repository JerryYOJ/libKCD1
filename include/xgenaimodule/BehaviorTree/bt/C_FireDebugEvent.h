#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <FireDebugEvent>.

namespace wh::xgenaimodule::BehaviorTree {

// <FireDebugEvent>  RTTI C_FireDebugEvent  vtable 0x182390e08  size 0x28  base C_Node  ctx S_BaseNodeContext
class C_FireDebugEvent : public C_NodeWrapper<C_FireDebugEvent, C_Node, S_BaseNodeContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_FireDebugEvent;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_FireDebugEvent) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
