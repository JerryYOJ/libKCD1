#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_ForwardingData.h"
#include "../C_Composite.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <GraphSearch>.

namespace wh::xgenaimodule::BehaviorTree {

// <GraphSearch>  RTTI C_GraphSearch  vtable 0x1821c35f0  size 0x58  base C_ForwardingData<C_Composite>  ctx S_GraphSearchContext
struct S_GraphSearchContext;
class C_GraphSearch : public C_NodeWrapper<C_GraphSearch, C_ForwardingData<C_Composite>, S_GraphSearchContext>
{
    uint8_t _ownState[0x18];   // [UNVERIFIED] own members above C_ForwardingData<C_Composite> (0x40)
};
static_assert(sizeof(C_GraphSearch) == 0x58);

}  // namespace wh::xgenaimodule::BehaviorTree
