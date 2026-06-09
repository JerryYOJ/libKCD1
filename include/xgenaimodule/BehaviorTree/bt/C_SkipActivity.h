#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <SkipActivity>.

namespace wh::xgenaimodule::BehaviorTree {

// <SkipActivity>  RTTI C_SkipActivity  vtable 0x18238a750  size 0x28  base C_Node  ctx S_SkipActivityContext
struct S_SkipActivityContext;
class C_SkipActivity : public C_NodeWrapper<C_SkipActivity, C_Node, S_SkipActivityContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_SkipActivity;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_SkipActivity) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
