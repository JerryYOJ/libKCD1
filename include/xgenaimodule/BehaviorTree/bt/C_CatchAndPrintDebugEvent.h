#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Decorator.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <CatchAndPrintDebugEvent>.

namespace wh::xgenaimodule::BehaviorTree {

// <CatchAndPrintDebugEvent>  RTTI C_CatchAndPrintDebugEvent  vtable 0x182391078  size 0x30  base C_Decorator  ctx S_CatchAndPrintDebugEventContext
struct S_CatchAndPrintDebugEventContext;
class C_CatchAndPrintDebugEvent : public C_NodeWrapper<C_CatchAndPrintDebugEvent, C_Decorator, S_CatchAndPrintDebugEventContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_CatchAndPrintDebugEvent;
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_CatchAndPrintDebugEvent) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
