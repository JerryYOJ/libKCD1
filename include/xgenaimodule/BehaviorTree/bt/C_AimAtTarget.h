#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Decorator.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <AimAtTarget>.

namespace wh::xgenaimodule::BehaviorTree {

// <AimAtTarget>  RTTI C_AimAtTarget  vtable 0x1823576c8  size 0x30  base C_WrapperDecorator  ctx S_AimAtTargetContext
struct S_AimAtTargetContext;
class C_AimAtTarget : public C_NodeWrapper<C_AimAtTarget, C_WrapperDecorator, S_AimAtTargetContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_AimAtTarget;
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_AimAtTarget) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
