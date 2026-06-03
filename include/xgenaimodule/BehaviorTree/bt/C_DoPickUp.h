#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_AnimatedAction.h"
#include "C_InstantDoPickUp.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <DoPickUp>.

namespace wh::xgenaimodule::BehaviorTree {

// <DoPickUp>  RTTI C_DoPickUp  vtable 0x1821d55a8  size 0x28  base C_InstantDoPickUp<C_AnimatedAction<C_PickUpItemAnimAction>>  ctx S_DoPickUpContext
struct S_DoPickUpContext;
class C_DoPickUp : public C_NodeWrapper<C_DoPickUp, C_InstantDoPickUp<C_AnimatedAction<C_PickUpItemAnimAction>>, S_DoPickUpContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_DoPickUp) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
