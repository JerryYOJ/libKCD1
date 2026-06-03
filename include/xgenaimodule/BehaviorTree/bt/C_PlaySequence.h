#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Barrier.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <PlaySequence>.

namespace wh::xgenaimodule::BehaviorTree {

// <PlaySequence>  RTTI C_PlaySequence  vtable 0x1826ed200  size 0x38  base C_PassiveBarrier  ctx S_PlaySequenceContext
struct S_PlaySequenceContext;
class C_PlaySequence : public C_NodeWrapper<C_PlaySequence, C_PassiveBarrier, S_PlaySequenceContext>
{
    uint8_t _ownState[0x8];   // [UNVERIFIED] own members above C_PassiveBarrier (0x30)
};
static_assert(sizeof(C_PlaySequence) == 0x38);

}  // namespace wh::xgenaimodule::BehaviorTree
