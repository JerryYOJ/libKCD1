#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <EnableProfile>.

namespace wh::xgenaimodule::BehaviorTree {

// <EnableProfile>  RTTI C_EnableProfile  vtable 0x182324d38  size 0x28  base C_Node  ctx S_EnableProfileContext
struct S_EnableProfileContext;
class C_EnableProfile : public C_NodeWrapper<C_EnableProfile, C_Node, S_EnableProfileContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_EnableProfile;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_EnableProfile) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
