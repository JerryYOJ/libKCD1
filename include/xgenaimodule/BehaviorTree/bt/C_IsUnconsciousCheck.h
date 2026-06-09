#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_NPCStateCheckBase.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <IsUnconsciousCheck>.

namespace wh::xgenaimodule::BehaviorTree {

// <IsUnconsciousCheck>  RTTI C_IsUnconsciousCheck  vtable 0x18220b450  size 0x68  base C_NPCStateCheckBase  ctx S_NPCStateCheckBaseContext
struct S_NPCStateCheckBaseContext;
class C_IsUnconsciousCheck : public C_NodeWrapper<C_IsUnconsciousCheck, C_NPCStateCheckBase, S_NPCStateCheckBaseContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_IsUnconsciousCheck;
    // no own data members (object == 0x68)
};
static_assert(sizeof(C_IsUnconsciousCheck) == 0x68);

}  // namespace wh::xgenaimodule::BehaviorTree
