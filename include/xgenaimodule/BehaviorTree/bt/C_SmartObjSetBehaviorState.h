#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <SmartObjSetBehaviorState>.

namespace wh::xgenaimodule::BehaviorTree {

// <SmartObjSetBehaviorState>  RTTI C_SmartObjSetBehaviorState  vtable 0x182215d68  size 0x28  base C_Node  ctx S_SmartObjSetBehaviorStateContext
struct S_SmartObjSetBehaviorStateContext;
class C_SmartObjSetBehaviorState : public C_NodeWrapper<C_SmartObjSetBehaviorState, C_Node, S_SmartObjSetBehaviorStateContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_SmartObjSetBehaviorState;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_SmartObjSetBehaviorState) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
