#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_NPCStateCheckBase.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <HasActiveThreats>.

namespace wh::xgenaimodule::BehaviorTree {

// <HasActiveThreats>  RTTI C_HasActiveThreats  vtable 0x182388ea0  size 0x68  base C_NPCStateCheckBase  ctx S_NPCStateCheckBaseContext
struct S_NPCStateCheckBaseContext;
class C_HasActiveThreats : public C_NodeWrapper<C_HasActiveThreats, C_NPCStateCheckBase, S_NPCStateCheckBaseContext>
{
    // no own data members (object == 0x68)
};
static_assert(sizeof(C_HasActiveThreats) == 0x68);

}  // namespace wh::xgenaimodule::BehaviorTree
