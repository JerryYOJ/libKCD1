#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <FireArrow>.

namespace wh::xgenaimodule::BehaviorTree {

// <FireArrow>  RTTI C_FireArrow  vtable 0x182354090  size 0x28  base C_Node  ctx S_FireArrowContext
struct S_FireArrowContext;
class C_FireArrow : public C_NodeWrapper<C_FireArrow, C_Node, S_FireArrowContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_FireArrow;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_FireArrow) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
