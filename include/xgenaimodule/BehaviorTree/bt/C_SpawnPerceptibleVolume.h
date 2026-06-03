#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <SpawnPerceptibleVolume>.

namespace wh::xgenaimodule::BehaviorTree {

// <SpawnPerceptibleVolume>  RTTI C_SpawnPerceptibleVolume  vtable 0x18238b8a8  size 0x28  base C_Node  ctx S_SpawnPerceptibleVolumeContext
struct S_SpawnPerceptibleVolumeContext;
class C_SpawnPerceptibleVolume : public C_NodeWrapper<C_SpawnPerceptibleVolume, C_Node, S_SpawnPerceptibleVolumeContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_SpawnPerceptibleVolume) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
