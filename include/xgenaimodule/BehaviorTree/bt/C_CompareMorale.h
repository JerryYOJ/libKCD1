#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Gate.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <CompareMorale>.

namespace wh::xgenaimodule::BehaviorTree {

// <CompareMorale>  RTTI C_CompareMorale  vtable 0x18238a0a0  size 0x68  base C_Gate  ctx S_CompareMoraleContext
struct S_CompareMoraleContext;
class C_CompareMorale : public C_NodeWrapper<C_CompareMorale, C_Gate, S_CompareMoraleContext>
{
    // no own data members (object == 0x68)
};
static_assert(sizeof(C_CompareMorale) == 0x68);

}  // namespace wh::xgenaimodule::BehaviorTree
