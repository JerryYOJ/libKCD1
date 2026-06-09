#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_MakeIdleBase.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <Teleport>.

namespace wh::xgenaimodule::BehaviorTree {

// <Teleport>  RTTI C_Teleport  vtable 0x1822021e0  size 0x28  base C_MakeIdleBase  ctx S_TeleportContext
struct S_TeleportContext;
class C_Teleport : public C_NodeWrapper<C_Teleport, C_MakeIdleBase, S_TeleportContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_Teleport;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_Teleport) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
