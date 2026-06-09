#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <NumericalOperation>.

namespace wh::xgenaimodule::BehaviorTree {

// <NumericalOperation>  RTTI C_NumericalOperation  vtable ?  size 0x28  base C_Node  ctx S_NumericalOperationContext
struct S_NumericalOperationContext;
class C_NumericalOperation : public C_NodeWrapper<C_NumericalOperation, C_Node, S_NumericalOperationContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_NumericalOperation;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_NumericalOperation) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
