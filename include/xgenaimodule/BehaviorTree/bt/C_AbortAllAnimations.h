#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <AbortAllAnimations>.

namespace wh::xgenaimodule::BehaviorTree {

// <AbortAllAnimations>  RTTI C_AbortAllAnimations  vtable 0x18220dda8  size 0x28  base C_Node  ctx S_AbortAllAnimationsContext
struct S_AbortAllAnimationsContext;
class C_AbortAllAnimations : public C_NodeWrapper<C_AbortAllAnimations, C_Node, S_AbortAllAnimationsContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_AbortAllAnimations;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_AbortAllAnimations) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
