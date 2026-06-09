#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Gate.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <StateMachineCheck>.

namespace wh::xgenaimodule::BehaviorTree {

// <StateMachineCheck>  RTTI C_StateMachineCheck  vtable 0x182364580  size 0x68  base C_Gate  ctx S_StateMachineCheckContext
struct S_StateMachineCheckContext;
class C_StateMachineCheck : public C_NodeWrapper<C_StateMachineCheck, C_Gate, S_StateMachineCheckContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_StateMachineCheck;
    // no own data members (object == 0x68)
};
static_assert(sizeof(C_StateMachineCheck) == 0x68);

}  // namespace wh::xgenaimodule::BehaviorTree
