#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Gate.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <LODCheck>.

namespace wh::xgenaimodule::BehaviorTree {

// <LODCheck>  RTTI C_LODCheck  vtable 0x18219e7a0  size 0x68  base C_Gate  ctx S_LODCheckContext
struct S_LODCheckContext;
class C_LODCheck : public C_NodeWrapper<C_LODCheck, C_Gate, S_LODCheckContext>
{
    // no own data members (object == 0x68)
};
static_assert(sizeof(C_LODCheck) == 0x68);

}  // namespace wh::xgenaimodule::BehaviorTree
