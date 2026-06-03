#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Composite.h"
#include "C_LinkModifier.h"
#include "C_LinkNoData.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <NegationOp>.

namespace wh::xgenaimodule::BehaviorTree {

// <NegationOp>  RTTI C_NegationOp  vtable 0x1821da448  size 0x50  base C_LinkModifier<C_LinkNoData<C_FixedComposite<1>>, I_LinkFilter>  ctx S_NegationOpContext
struct S_NegationOpContext;
class C_NegationOp : public C_NodeWrapper<C_NegationOp, C_LinkModifier<C_LinkNoData<C_FixedComposite<1>>, I_LinkFilter>, S_NegationOpContext>
{
    uint8_t _ownState[0x20];   // [UNVERIFIED] own members above C_LinkModifier<C_LinkNoData<C_FixedComposite<1>>, I_LinkFilter> (0x30)
};
static_assert(sizeof(C_NegationOp) == 0x50);

}  // namespace wh::xgenaimodule::BehaviorTree
