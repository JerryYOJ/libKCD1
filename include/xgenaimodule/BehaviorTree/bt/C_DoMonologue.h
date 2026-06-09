#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_DefferedStateChange.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <DoMonologue>.

namespace wh::xgenaimodule::BehaviorTree {

// <DoMonologue>  RTTI C_DoMonologue  vtable 0x1823251e8  size 0x28  base C_DefferedStateChange  ctx S_DoMonologueContext
struct S_DoMonologueContext;
class C_DoMonologue : public C_NodeWrapper<C_DoMonologue, C_DefferedStateChange, S_DoMonologueContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_DoMonologue;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_DoMonologue) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
