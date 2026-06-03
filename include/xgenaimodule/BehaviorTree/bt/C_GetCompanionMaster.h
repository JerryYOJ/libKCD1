#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <GetCompanionMaster>.

namespace wh::xgenaimodule::BehaviorTree {

// <GetCompanionMaster>  RTTI C_GetCompanionMaster  vtable 0x1822170e8  size 0x28  base C_Node  ctx S_GetCompanionMasterContext
struct S_GetCompanionMasterContext;
class C_GetCompanionMaster : public C_NodeWrapper<C_GetCompanionMaster, C_Node, S_GetCompanionMasterContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_GetCompanionMaster) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
