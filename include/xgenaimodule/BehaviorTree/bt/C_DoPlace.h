#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_AnimatedAction.h"
#include "C_InstantDoPlace.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <DoPlace>.

namespace wh::xgenaimodule::BehaviorTree {

// <DoPlace>  RTTI C_DoPlace  vtable 0x182212ea8  size 0x28  base C_InstantDoPlace<C_AnimatedAction<C_PlaceItemAnimAction>>  ctx S_DoPlaceContext
struct S_DoPlaceContext;
class C_DoPlace : public C_NodeWrapper<C_DoPlace, C_InstantDoPlace<C_AnimatedAction<C_PlaceItemAnimAction>>, S_DoPlaceContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_DoPlace) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
