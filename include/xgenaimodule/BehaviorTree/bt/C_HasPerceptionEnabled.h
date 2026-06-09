#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Gate.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <HasPerceptionEnabled>.

namespace wh::xgenaimodule::BehaviorTree {

// <HasPerceptionEnabled>  RTTI C_HasPerceptionEnabled  vtable 0x18238c278  size 0x68  base C_Gate  ctx S_HasPerceptionEnabledContext
struct S_HasPerceptionEnabledContext;
class C_HasPerceptionEnabled : public C_NodeWrapper<C_HasPerceptionEnabled, C_Gate, S_HasPerceptionEnabledContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_HasPerceptionEnabled;
    // no own data members (object == 0x68)
};
static_assert(sizeof(C_HasPerceptionEnabled) == 0x68);

}  // namespace wh::xgenaimodule::BehaviorTree
