#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Decorator.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <SuspendRandomEvents>.

namespace wh::xgenaimodule::BehaviorTree {

// <SuspendRandomEvents>  RTTI C_SuspendRandomEvents  vtable 0x18234a7a8  size 0x30  base C_WrapperDecorator  ctx S_WrapperDecoratorContext
struct S_WrapperDecoratorContext;
class C_SuspendRandomEvents : public C_NodeWrapper<C_SuspendRandomEvents, C_WrapperDecorator, S_WrapperDecoratorContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_SuspendRandomEvents;
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_SuspendRandomEvents) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
