#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <Look>.

namespace wh::xgenaimodule::BehaviorTree {

// <Look>  RTTI C_Look  vtable ?  size 0x28  base C_Node  ctx S_LookContext
struct S_LookContext;
class C_Look : public C_NodeWrapper<C_Look, C_Node, S_LookContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_Look;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_Look) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
