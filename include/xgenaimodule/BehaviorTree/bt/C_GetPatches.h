#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <GetPatches>.

namespace wh::xgenaimodule::BehaviorTree {

// <GetPatches>  RTTI C_GetPatches  vtable 0x18238be68  size 0x28  base C_Node  ctx S_GetPatchesContext
struct S_GetPatchesContext;
class C_GetPatches : public C_NodeWrapper<C_GetPatches, C_Node, S_GetPatchesContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_GetPatches;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_GetPatches) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
