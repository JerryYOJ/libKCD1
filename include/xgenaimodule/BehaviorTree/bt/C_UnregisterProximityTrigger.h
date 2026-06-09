#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <UnregisterProximityTrigger>.

namespace wh::xgenaimodule::BehaviorTree {

// <UnregisterProximityTrigger>  RTTI C_UnregisterProximityTrigger  vtable 0x182347b90  size 0x28  base C_Node  ctx S_UnregisterProximityTriggerContext
struct S_UnregisterProximityTriggerContext;
class C_UnregisterProximityTrigger : public C_NodeWrapper<C_UnregisterProximityTrigger, C_Node, S_UnregisterProximityTriggerContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_UnregisterProximityTrigger;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_UnregisterProximityTrigger) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
