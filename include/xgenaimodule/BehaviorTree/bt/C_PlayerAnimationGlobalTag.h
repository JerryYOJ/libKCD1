#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Decorator.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <PlayerAnimationGlobalTag>.

namespace wh::xgenaimodule::BehaviorTree {

// <PlayerAnimationGlobalTag>  RTTI C_PlayerAnimationGlobalTag  vtable 0x18233de18  size 0x30  base C_WrapperDecorator  ctx S_PlayerAnimationGlobalTagContext
struct S_PlayerAnimationGlobalTagContext;
class C_PlayerAnimationGlobalTag : public C_NodeWrapper<C_PlayerAnimationGlobalTag, C_WrapperDecorator, S_PlayerAnimationGlobalTagContext>
{
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_PlayerAnimationGlobalTag) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
