#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <GetActivity>.

namespace wh::xgenaimodule::BehaviorTree {

// <GetActivity>  RTTI C_GetActivity  vtable 0x18238bbf8  size 0x28  base C_Node  ctx S_GetActivityContext
struct S_GetActivityContext;
class C_GetActivity : public C_NodeWrapper<C_GetActivity, C_Node, S_GetActivityContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_GetActivity;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_GetActivity) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
