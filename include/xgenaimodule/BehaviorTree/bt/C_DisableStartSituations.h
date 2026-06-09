#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Decorator.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <DisableStartSituations>.

namespace wh::xgenaimodule::BehaviorTree {

// <DisableStartSituations>  RTTI C_DisableStartSituations  vtable 0x18235f218  size 0x30  base C_WrapperDecorator  ctx S_WrapperDecoratorContext
struct S_WrapperDecoratorContext;
class C_DisableStartSituations : public C_NodeWrapper<C_DisableStartSituations, C_WrapperDecorator, S_WrapperDecoratorContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_DisableStartSituations;
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_DisableStartSituations) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
