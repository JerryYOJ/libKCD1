#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Gate.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <IsInsideArea>.

namespace wh::xgenaimodule::BehaviorTree {

// <IsInsideArea>  RTTI C_IsInsideArea  vtable 0x18235d6f8  size 0x68  base C_Gate  ctx S_IsInsideAreaContext
struct S_IsInsideAreaContext;
class C_IsInsideArea : public C_NodeWrapper<C_IsInsideArea, C_Gate, S_IsInsideAreaContext>
{
    // no own data members (object == 0x68)
};
static_assert(sizeof(C_IsInsideArea) == 0x68);

}  // namespace wh::xgenaimodule::BehaviorTree
