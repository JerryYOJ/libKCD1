#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_LinkFilterWithSource.h"
#include "../C_Node.h"
#include "C_LinkLimitedData.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <SoulIsAliveFilter>.

namespace wh::xgenaimodule::BehaviorTree {

// <SoulIsAliveFilter>  RTTI C_SoulIsAliveFilter  vtable 0x1826ffbf8  size 0x30  base C_LinkFilterWithSource<C_SoulIsAliveFilter, C_LinkLimitedData<C_Node>>  ctx S_SoulIsAliveFilterContext
struct S_SoulIsAliveFilterContext;
class C_SoulIsAliveFilter : public C_NodeWrapper<C_SoulIsAliveFilter, C_LinkFilterWithSource<C_SoulIsAliveFilter, C_LinkLimitedData<C_Node>>, S_SoulIsAliveFilterContext>
{
    uint8_t _ownState[0x8];   // [UNVERIFIED] own members above C_LinkFilterWithSource<C_SoulIsAliveFilter, C_LinkLimitedData<C_Node>> (0x28)
};
static_assert(sizeof(C_SoulIsAliveFilter) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
