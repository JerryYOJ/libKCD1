#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Composite.h"
#include "C_LinkModifier.h"
#include "C_LinkNoData.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <OnPathFilter>.

namespace wh::xgenaimodule::BehaviorTree {

// <OnPathFilter>  RTTI C_OnPathFilter  vtable 0x1826fea20  size 0x50  base C_LinkModifier<C_LinkNoData<C_FixedComposite<1>>, I_LinkFilter>  ctx S_OnPathFilterContext
struct S_OnPathFilterContext;
class C_OnPathFilter : public C_NodeWrapper<C_OnPathFilter, C_LinkModifier<C_LinkNoData<C_FixedComposite<1>>, I_LinkFilter>, S_OnPathFilterContext>
{
    uint8_t _ownState[0x20];   // [UNVERIFIED] own members above C_LinkModifier<C_LinkNoData<C_FixedComposite<1>>, I_LinkFilter> (0x30)
};
static_assert(sizeof(C_OnPathFilter) == 0x50);

}  // namespace wh::xgenaimodule::BehaviorTree
