#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Barrier.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <DLCInstallGate>.

namespace wh::xgenaimodule::BehaviorTree {

// <DLCInstallGate>  RTTI C_DLCInstallGate  vtable 0x18236d678  size 0x30  base C_PassiveBarrier  ctx S_DLCInstallGateContext
struct S_DLCInstallGateContext;
class C_DLCInstallGate : public C_NodeWrapper<C_DLCInstallGate, C_PassiveBarrier, S_DLCInstallGateContext>
{
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_DLCInstallGate) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
