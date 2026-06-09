#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Decorator.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <RepushTest>.

namespace wh::xgenaimodule::BehaviorTree {

// <RepushTest>  RTTI C_RepushTest  vtable 0x182390800  size 0x30  base C_Decorator  ctx S_RepushTestContext
struct S_RepushTestContext;
class C_RepushTest : public C_NodeWrapper<C_RepushTest, C_Decorator, S_RepushTestContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_RepushTest;
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_RepushTest) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
