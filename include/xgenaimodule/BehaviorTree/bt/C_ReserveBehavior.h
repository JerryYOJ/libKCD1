#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Composite.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <ReserveBehavior>.

namespace wh::xgenaimodule::BehaviorTree {

// <ReserveBehavior>  RTTI C_ReserveBehavior  vtable 0x182208318  size 0x68  base C_FixedComposite<2>  ctx S_ReserveBehaviorContext
struct S_ReserveBehaviorContext;
class C_ReserveBehavior : public C_NodeWrapper<C_ReserveBehavior, C_FixedComposite<2>, S_ReserveBehaviorContext>
{
    uint8_t _ownState[0x30];   // [UNVERIFIED] own members above C_FixedComposite<2> (0x38)
};
static_assert(sizeof(C_ReserveBehavior) == 0x68);

}  // namespace wh::xgenaimodule::BehaviorTree
