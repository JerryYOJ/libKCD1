#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_SpawnPerceptibleVolume.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <SpawnExpiringPerceptibleVolume>.

namespace wh::xgenaimodule::BehaviorTree {

// <SpawnExpiringPerceptibleVolume>  RTTI C_SpawnExpiringPerceptibleVolume  vtable 0x18238b4b8  size 0x28  base C_SpawnPerceptibleVolume  ctx S_SpawnExpiringPerceptibleVolumeContext
struct S_SpawnExpiringPerceptibleVolumeContext;
class C_SpawnExpiringPerceptibleVolume : public C_NodeWrapper<C_SpawnExpiringPerceptibleVolume, C_SpawnPerceptibleVolume, S_SpawnExpiringPerceptibleVolumeContext>
{
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_SpawnExpiringPerceptibleVolume) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
