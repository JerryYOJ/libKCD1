#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_CombatNode.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <InstantSetTarget>.

namespace wh::xgenaimodule::BehaviorTree {

// <InstantSetTarget>  RTTI C_InstantSetTarget  vtable 0x1821f8a08  size 0x28  base C_CombatNode<C_Node>  ctx S_InstantSetTargetContext
struct S_InstantSetTargetContext;
class C_InstantSetTarget : public C_NodeWrapper<C_InstantSetTarget, C_CombatNode<C_Node>, S_InstantSetTargetContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_InstantSetTarget;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_InstantSetTarget) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
