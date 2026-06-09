#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Decorator.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <DisableCollisionAvoidance>.

namespace wh::xgenaimodule::BehaviorTree {

// <DisableCollisionAvoidance>  RTTI C_DisableCollisionAvoidance  vtable 0x18235fbf8  size 0x30  base C_WrapperDecorator  ctx S_DisableCollisionAvoidanceContext
struct S_DisableCollisionAvoidanceContext;
class C_DisableCollisionAvoidance : public C_NodeWrapper<C_DisableCollisionAvoidance, C_WrapperDecorator, S_DisableCollisionAvoidanceContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_DisableCollisionAvoidance;
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_DisableCollisionAvoidance) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
