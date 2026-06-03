#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_NPCStateCheckBase.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <IsDeadCheck>.

namespace wh::xgenaimodule::BehaviorTree {

// <IsDeadCheck>  RTTI C_IsDeadCheck  vtable 0x18219eca0  size 0x68  base C_NPCStateCheckBase  ctx S_NPCStateCheckBaseContext
struct S_NPCStateCheckBaseContext;
class C_IsDeadCheck : public C_NodeWrapper<C_IsDeadCheck, C_NPCStateCheckBase, S_NPCStateCheckBaseContext>
{
    // no own data members (object == 0x68)
};
static_assert(sizeof(C_IsDeadCheck) == 0x68);

}  // namespace wh::xgenaimodule::BehaviorTree
