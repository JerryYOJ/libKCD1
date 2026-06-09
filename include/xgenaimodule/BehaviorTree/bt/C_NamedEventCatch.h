#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Decorator.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <NamedEventCatch>.

namespace wh::xgenaimodule::BehaviorTree {

// <NamedEventCatch>  RTTI C_NamedEventCatch  vtable 0x182701ee8  size 0x38  base C_Decorator  ctx S_NamedEventCatchContext
struct S_NamedEventCatchContext;
class C_NamedEventCatch : public C_NodeWrapper<C_NamedEventCatch, C_Decorator, S_NamedEventCatchContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_NamedEventCatch;
    uint8_t _ownState[0x8];   // [UNVERIFIED] own members above C_Decorator (0x30)
};
static_assert(sizeof(C_NamedEventCatch) == 0x38);

}  // namespace wh::xgenaimodule::BehaviorTree
