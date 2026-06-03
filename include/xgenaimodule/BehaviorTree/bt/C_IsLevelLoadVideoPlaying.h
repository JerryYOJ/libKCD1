#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_ActiveBarrier.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <IsLevelLoadVideoPlaying>.

namespace wh::xgenaimodule::BehaviorTree {

// <IsLevelLoadVideoPlaying>  RTTI C_IsLevelLoadVideoPlaying  vtable 0x18236be50  size 0x30  base C_ActiveBarrier  ctx S_IsLevelLoadVideoPlayingContext
struct S_IsLevelLoadVideoPlayingContext;
class C_IsLevelLoadVideoPlaying : public C_NodeWrapper<C_IsLevelLoadVideoPlaying, C_ActiveBarrier, S_IsLevelLoadVideoPlayingContext>
{
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_IsLevelLoadVideoPlaying) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
