#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <RemovePatch>.

namespace wh::xgenaimodule::BehaviorTree {

// <RemovePatch>  RTTI C_RemovePatch  vtable 0x18238a498  size 0x28  base C_Node  ctx S_RemovePatchContext
struct S_RemovePatchContext;
class C_RemovePatch : public C_NodeWrapper<C_RemovePatch, C_Node, S_RemovePatchContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_RemovePatch;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_RemovePatch) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
