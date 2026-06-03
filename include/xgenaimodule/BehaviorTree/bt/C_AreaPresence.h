#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Decorator.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <AreaPresence>.

namespace wh::xgenaimodule::BehaviorTree {

// <AreaPresence>  RTTI C_AreaPresence  vtable 0x18220fe88  size 0x30  base C_Decorator  ctx S_AreaPresenceContext
struct S_AreaPresenceContext;
class C_AreaPresence : public C_NodeWrapper<C_AreaPresence, C_Decorator, S_AreaPresenceContext>
{
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_AreaPresence) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
