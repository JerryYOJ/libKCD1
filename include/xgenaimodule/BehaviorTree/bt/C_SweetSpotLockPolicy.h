#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <SweetSpotLockPolicy>.

namespace wh::xgenaimodule::BehaviorTree {

// <SweetSpotLockPolicy>  RTTI C_SweetSpotLockPolicy  vtable 0x18236cfa0  size 0x28  base C_Node  ctx S_SweetSpotLockPolicyContext
struct S_SweetSpotLockPolicyContext;
class C_SweetSpotLockPolicy : public C_NodeWrapper<C_SweetSpotLockPolicy, C_Node, S_SweetSpotLockPolicyContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_SweetSpotLockPolicy;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_SweetSpotLockPolicy) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
