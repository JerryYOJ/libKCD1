#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_RepushTest.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <RepushTestKeepThreads>.

namespace wh::xgenaimodule::BehaviorTree {

// <RepushTestKeepThreads>  RTTI C_RepushTestKeepThreads  vtable 0x182390590  size 0x30  base C_RepushTest  ctx S_RepushTestContext
struct S_RepushTestContext;
class C_RepushTestKeepThreads : public C_NodeWrapper<C_RepushTestKeepThreads, C_RepushTest, S_RepushTestContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_RepushTestKeepThreads;
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_RepushTestKeepThreads) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
