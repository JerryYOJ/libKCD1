#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <CheckGlobalTagState>.

namespace wh::xgenaimodule::BehaviorTree {

// <CheckGlobalTagState>  RTTI C_CheckGlobalTagState  vtable 0x18231d190  size 0x28  base C_Node  ctx S_CheckGlobalTagStateContext
struct S_CheckGlobalTagStateContext;
class C_CheckGlobalTagState : public C_NodeWrapper<C_CheckGlobalTagState, C_Node, S_CheckGlobalTagStateContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_CheckGlobalTagState;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_CheckGlobalTagState) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
