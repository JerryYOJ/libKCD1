#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <DeSpawnPerceptibleVolume>.

namespace wh::xgenaimodule::BehaviorTree {

// <DeSpawnPerceptibleVolume>  RTTI C_DeSpawnPerceptibleVolume  vtable 0x1823801c0  size 0x28  base C_Node  ctx S_DeSpawnPerceptibleVolumeContext
struct S_DeSpawnPerceptibleVolumeContext;
class C_DeSpawnPerceptibleVolume : public C_NodeWrapper<C_DeSpawnPerceptibleVolume, C_Node, S_DeSpawnPerceptibleVolumeContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_DeSpawnPerceptibleVolume) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
