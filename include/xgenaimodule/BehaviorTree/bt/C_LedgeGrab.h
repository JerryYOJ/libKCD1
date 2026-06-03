#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_DefferedStateChange.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <LedgeGrab>.

namespace wh::xgenaimodule::BehaviorTree {

// <LedgeGrab>  RTTI C_LedgeGrab  vtable 0x182222a50  size 0x28  base C_DefferedStateChange  ctx S_LedgeGrabContext
struct S_LedgeGrabContext;
class C_LedgeGrab : public C_NodeWrapper<C_LedgeGrab, C_DefferedStateChange, S_LedgeGrabContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_LedgeGrab) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
