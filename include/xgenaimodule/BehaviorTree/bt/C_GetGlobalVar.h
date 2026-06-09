#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <GetGlobalVar>.

namespace wh::xgenaimodule::BehaviorTree {

// <GetGlobalVar>  RTTI C_GetGlobalVar  vtable 0x1823234e8  size 0x28  base C_Node  ctx S_GetGlobalVarContext
struct S_GetGlobalVarContext;
class C_GetGlobalVar : public C_NodeWrapper<C_GetGlobalVar, C_Node, S_GetGlobalVarContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_GetGlobalVar;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_GetGlobalVar) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
