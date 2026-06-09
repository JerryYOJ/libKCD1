#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Gate.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <IsInsideAreaWithLabel>.

namespace wh::xgenaimodule::BehaviorTree {

// <IsInsideAreaWithLabel>  RTTI C_IsInsideAreaWithLabel  vtable 0x1822124a8  size 0x68  base C_Gate  ctx S_IsInsideAreaWithLabelContext
struct S_IsInsideAreaWithLabelContext;
class C_IsInsideAreaWithLabel : public C_NodeWrapper<C_IsInsideAreaWithLabel, C_Gate, S_IsInsideAreaWithLabelContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_IsInsideAreaWithLabel;
    // no own data members (object == 0x68)
};
static_assert(sizeof(C_IsInsideAreaWithLabel) == 0x68);

}  // namespace wh::xgenaimodule::BehaviorTree
