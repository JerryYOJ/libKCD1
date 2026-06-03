#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_ActiveBarrier.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <StreamingInstallGate>.

namespace wh::xgenaimodule::BehaviorTree {

// <StreamingInstallGate>  RTTI C_StreamingInstallGate  vtable 0x182376fa8  size 0x30  base C_ActiveBarrier  ctx S_StreamingInstallGateContext
struct S_StreamingInstallGateContext;
class C_StreamingInstallGate : public C_NodeWrapper<C_StreamingInstallGate, C_ActiveBarrier, S_StreamingInstallGateContext>
{
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_StreamingInstallGate) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
