#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Decorator.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <AllowSituations>.

namespace wh::xgenaimodule::BehaviorTree {

// <AllowSituations>  RTTI C_AllowSituations  vtable 0x1821ee818  size 0x30  base C_WrapperDecorator  ctx S_AllowSituationsContext
struct S_AllowSituationsContext;
class C_AllowSituations : public C_NodeWrapper<C_AllowSituations, C_WrapperDecorator, S_AllowSituationsContext>
{
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_AllowSituations) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
