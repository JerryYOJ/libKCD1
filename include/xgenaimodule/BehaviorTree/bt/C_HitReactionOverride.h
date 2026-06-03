#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Decorator.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <HitReactionOverride>.

namespace wh::xgenaimodule::BehaviorTree {

// <HitReactionOverride>  RTTI C_HitReactionOverride  vtable 0x18235e4e8  size 0x30  base C_WrapperDecorator  ctx S_HitReactionOverrideContext
struct S_HitReactionOverrideContext;
class C_HitReactionOverride : public C_NodeWrapper<C_HitReactionOverride, C_WrapperDecorator, S_HitReactionOverrideContext>
{
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_HitReactionOverride) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
