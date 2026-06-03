#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_NPCStateCheckBase.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <HasGenderCheck>.

namespace wh::xgenaimodule::BehaviorTree {

// <HasGenderCheck>  RTTI C_HasGenderCheck  vtable 0x182389200  size 0x68  base C_NPCStateCheckBase  ctx S_HasGenderCheckContext
struct S_HasGenderCheckContext;
class C_HasGenderCheck : public C_NodeWrapper<C_HasGenderCheck, C_NPCStateCheckBase, S_HasGenderCheckContext>
{
    // no own data members (object == 0x68)
};
static_assert(sizeof(C_HasGenderCheck) == 0x68);

}  // namespace wh::xgenaimodule::BehaviorTree
