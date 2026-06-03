#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_DefferedStateChange.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <PlayVideo>.

namespace wh::xgenaimodule::BehaviorTree {

// <PlayVideo>  RTTI C_PlayVideo  vtable 0x1826ecf38  size 0x30  base C_DefferedStateChange  ctx S_PlayVideoContext
struct S_PlayVideoContext;
class C_PlayVideo : public C_NodeWrapper<C_PlayVideo, C_DefferedStateChange, S_PlayVideoContext>
{
    uint8_t _ownState[0x8];   // [UNVERIFIED] own members above C_DefferedStateChange (0x28)
};
static_assert(sizeof(C_PlayVideo) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
