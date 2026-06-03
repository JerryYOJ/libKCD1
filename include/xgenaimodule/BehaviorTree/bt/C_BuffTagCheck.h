#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Gate.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <BuffTagCheck>.

namespace wh::xgenaimodule::BehaviorTree {

// <BuffTagCheck>  RTTI C_BuffTagCheck  vtable 0x18238ab18  size 0x68  base C_Gate  ctx S_BuffTagCheckContext
struct S_BuffTagCheckContext;
class C_BuffTagCheck : public C_NodeWrapper<C_BuffTagCheck, C_Gate, S_BuffTagCheckContext>
{
    // no own data members (object == 0x68)
};
static_assert(sizeof(C_BuffTagCheck) == 0x68);

}  // namespace wh::xgenaimodule::BehaviorTree
