#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <BowLoad>.

namespace wh::xgenaimodule::BehaviorTree {

// <BowLoad>  RTTI C_BowLoad  vtable 0x1823463a0  size 0x28  base C_Node  ctx S_BowLoadContext
struct S_BowLoadContext;
class C_BowLoad : public C_NodeWrapper<C_BowLoad, C_Node, S_BowLoadContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_BowLoad;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_BowLoad) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
