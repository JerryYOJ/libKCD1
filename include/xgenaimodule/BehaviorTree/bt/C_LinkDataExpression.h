#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_ForwardingData.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <LinkDataExpression>.

namespace wh::xgenaimodule::BehaviorTree {

// <LinkDataExpression>  RTTI C_LinkDataExpression  vtable 0x18221d030  size 0x28  base C_ForwardingData<C_Node>  ctx S_LinkDataExpressionContext
struct S_LinkDataExpressionContext;
class C_LinkDataExpression : public C_NodeWrapper<C_LinkDataExpression, C_ForwardingData<C_Node>, S_LinkDataExpressionContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_LinkDataExpression) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
