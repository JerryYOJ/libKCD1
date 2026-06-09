#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Decorator.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <LogToLabel>.

namespace wh::xgenaimodule::BehaviorTree {

// <LogToLabel>  RTTI C_LogToLabel  vtable 0x1821edb88  size 0x30  base C_WrapperDecorator  ctx S_LogToLabelContext
struct S_LogToLabelContext;
class C_LogToLabel : public C_NodeWrapper<C_LogToLabel, C_WrapperDecorator, S_LogToLabelContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_LogToLabel;
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_LogToLabel) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
