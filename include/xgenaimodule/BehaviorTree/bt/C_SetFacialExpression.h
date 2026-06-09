#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <SetFacialExpression>.

namespace wh::xgenaimodule::BehaviorTree {

// <SetFacialExpression>  RTTI C_SetFacialExpression  vtable 0x18233a978  size 0x28  base C_Node  ctx S_SetFacialExpressionContext
struct S_SetFacialExpressionContext;
class C_SetFacialExpression : public C_NodeWrapper<C_SetFacialExpression, C_Node, S_SetFacialExpressionContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_SetFacialExpression;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_SetFacialExpression) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
