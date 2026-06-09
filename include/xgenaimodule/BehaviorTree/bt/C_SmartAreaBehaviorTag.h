#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_SmartEntityBehaviorTag.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <SmartAreaBehaviorTag>.

namespace wh::xgenaimodule::BehaviorTree {

// <SmartAreaBehaviorTag>  RTTI C_SmartAreaBehaviorTag  vtable 0x1821c5c10  size 0x38  base C_SmartEntityBehaviorTag  ctx S_SmartAreaBehaviorTagContext
struct S_SmartAreaBehaviorTagContext;
class C_SmartAreaBehaviorTag : public C_NodeWrapper<C_SmartAreaBehaviorTag, C_SmartEntityBehaviorTag, S_SmartAreaBehaviorTagContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_SmartAreaBehaviorTag;
    uint8_t _ownState[0x10];   // [UNVERIFIED] own members above C_SmartEntityBehaviorTag (0x28)
};
static_assert(sizeof(C_SmartAreaBehaviorTag) == 0x38);

}  // namespace wh::xgenaimodule::BehaviorTree
