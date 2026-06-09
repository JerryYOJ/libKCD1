#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <IgnorePerception>.

namespace wh::xgenaimodule::BehaviorTree {

// <IgnorePerception>  RTTI C_IgnorePerception  vtable 0x18238cc60  size 0x28  base C_Node  ctx S_IgnorePerceptionContext
struct S_IgnorePerceptionContext;
class C_IgnorePerception : public C_NodeWrapper<C_IgnorePerception, C_Node, S_IgnorePerceptionContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_IgnorePerception;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_IgnorePerception) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
