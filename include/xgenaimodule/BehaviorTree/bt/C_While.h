#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Decorator.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <While>.

namespace wh::xgenaimodule::BehaviorTree {

// <While>  RTTI C_While  vtable 0x1821e9e38  size 0x30  base C_Decorator  ctx S_WhileContext
struct S_WhileContext;
class C_While : public C_NodeWrapper<C_While, C_Decorator, S_WhileContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_While;
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_While) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
