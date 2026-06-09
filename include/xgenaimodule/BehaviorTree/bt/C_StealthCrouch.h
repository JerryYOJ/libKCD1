#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Decorator.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <StealthCrouch>.

namespace wh::xgenaimodule::BehaviorTree {

// <StealthCrouch>  RTTI C_StealthCrouch  vtable 0x182363fb0  size 0x30  base C_WrapperDecorator  ctx S_WrapperDecoratorContext
struct S_WrapperDecoratorContext;
class C_StealthCrouch : public C_NodeWrapper<C_StealthCrouch, C_WrapperDecorator, S_WrapperDecoratorContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_StealthCrouch;
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_StealthCrouch) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
