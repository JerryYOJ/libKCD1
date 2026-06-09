#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Decorator.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <AddPerceivableState>.

namespace wh::xgenaimodule::BehaviorTree {

// <AddPerceivableState>  RTTI C_AddPerceivableState  vtable 0x1821eed28  size 0x30  base C_WrapperDecorator  ctx S_AddPerceivableStateContext
struct S_AddPerceivableStateContext;
class C_AddPerceivableState : public C_NodeWrapper<C_AddPerceivableState, C_WrapperDecorator, S_AddPerceivableStateContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_AddPerceivableState;
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_AddPerceivableState) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
