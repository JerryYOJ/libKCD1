#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <SetDynamicInformationValue>.

namespace wh::xgenaimodule::BehaviorTree {

// <SetDynamicInformationValue>  RTTI C_SetDynamicInformationValue  vtable 0x18221d8c0  size 0x28  base C_Node  ctx S_SetDynamicInformationValueContext
struct S_SetDynamicInformationValueContext;
class C_SetDynamicInformationValue : public C_NodeWrapper<C_SetDynamicInformationValue, C_Node, S_SetDynamicInformationValueContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_SetDynamicInformationValue) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
