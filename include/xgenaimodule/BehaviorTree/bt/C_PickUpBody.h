#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_DefferedStateChange.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <PickUpBody>.

namespace wh::xgenaimodule::BehaviorTree {

// <PickUpBody>  RTTI C_PickUpBody  vtable 0x18233f3b8  size 0x28  base C_DefferedStateChange  ctx S_PickUpBodyContext
struct S_PickUpBodyContext;
class C_PickUpBody : public C_NodeWrapper<C_PickUpBody, C_DefferedStateChange, S_PickUpBodyContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_PickUpBody) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
