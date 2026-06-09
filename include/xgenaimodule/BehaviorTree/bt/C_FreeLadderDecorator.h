#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Decorator.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <FreeLadderDecorator>.

namespace wh::xgenaimodule::BehaviorTree {

// <FreeLadderDecorator>  RTTI C_FreeLadderDecorator  vtable 0x1821ef4c0  size 0x30  base C_WrapperDecorator  ctx S_FreeLadderDecoratorContext
struct S_FreeLadderDecoratorContext;
class C_FreeLadderDecorator : public C_NodeWrapper<C_FreeLadderDecorator, C_WrapperDecorator, S_FreeLadderDecoratorContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_FreeLadderDecorator;
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_FreeLadderDecorator) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
