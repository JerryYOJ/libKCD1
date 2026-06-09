#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <LogToConsole>.

namespace wh::xgenaimodule::BehaviorTree {

// <LogToConsole>  RTTI C_LogToConsole  vtable 0x1821fed88  size 0x28  base C_Node  ctx S_LogToConsoleContext
struct S_LogToConsoleContext;
class C_LogToConsole : public C_NodeWrapper<C_LogToConsole, C_Node, S_LogToConsoleContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_LogToConsole;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_LogToConsole) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
