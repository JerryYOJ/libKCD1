#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_ModifyMoraleContextBase.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <ModifyMorale>.

namespace wh::xgenaimodule::BehaviorTree {

// <ModifyMorale>  RTTI C_ModifyMorale  vtable 0x1823875b0  size 0x28  base C_ModifyMoraleContextBase  ctx S_ModifyMoraleContextBaseContext
struct S_ModifyMoraleContextBaseContext;
class C_ModifyMorale : public C_NodeWrapper<C_ModifyMorale, C_ModifyMoraleContextBase, S_ModifyMoraleContextBaseContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_ModifyMorale) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
