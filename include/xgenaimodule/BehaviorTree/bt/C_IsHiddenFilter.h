#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_LinkFilterWithSource.h"
#include "../C_Node.h"
#include "C_LinkLimitedData.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <IsHiddenFilter>.

namespace wh::xgenaimodule::BehaviorTree {

// <IsHiddenFilter>  RTTI C_IsHiddenFilter  vtable 0x1826ff050  size 0x30  base C_LinkFilterWithSource<C_IsHiddenFilter, C_LinkLimitedData<C_Node>>  ctx S_IsHiddenFilterContext
struct S_IsHiddenFilterContext;
class C_IsHiddenFilter : public C_NodeWrapper<C_IsHiddenFilter, C_LinkFilterWithSource<C_IsHiddenFilter, C_LinkLimitedData<C_Node>>, S_IsHiddenFilterContext>
{
    uint8_t _ownState[0x8];   // [UNVERIFIED] own members above C_LinkFilterWithSource<C_IsHiddenFilter, C_LinkLimitedData<C_Node>> (0x28)
};
static_assert(sizeof(C_IsHiddenFilter) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
