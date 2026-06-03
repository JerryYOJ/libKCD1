#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_WUIDFilter.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <IsItemInStashFilter>.

namespace wh::xgenaimodule::BehaviorTree {

// <IsItemInStashFilter>  RTTI C_IsItemInStashFilter  vtable 0x1826fe3e8  size 0x30  base C_WUIDFilter  ctx S_WUIDFilterContext
struct S_WUIDFilterContext;
class C_IsItemInStashFilter : public C_NodeWrapper<C_IsItemInStashFilter, C_WUIDFilter, S_WUIDFilterContext>
{
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_IsItemInStashFilter) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
