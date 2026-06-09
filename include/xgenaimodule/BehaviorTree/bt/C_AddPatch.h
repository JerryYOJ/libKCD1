#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <AddPatch>.

namespace wh::xgenaimodule::BehaviorTree {

// <AddPatch>  RTTI C_AddPatch  vtable 0x18238ae80  size 0x28  base C_Node  ctx S_AddPatchContext
struct S_AddPatchContext;
class C_AddPatch : public C_NodeWrapper<C_AddPatch, C_Node, S_AddPatchContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_AddPatch;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_AddPatch) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
