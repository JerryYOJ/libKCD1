#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_SmartEntityBehaviorTag.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <SmartObjectBehaviorTag>.

namespace wh::xgenaimodule::BehaviorTree {

// <SmartObjectBehaviorTag>  RTTI C_SmartObjectBehaviorTag  vtable 0x1821c6170  size 0x38  base C_SmartEntityBehaviorTag  ctx S_SmartObjectBehaviorTagContext
struct S_SmartObjectBehaviorTagContext;
class C_SmartObjectBehaviorTag : public C_NodeWrapper<C_SmartObjectBehaviorTag, C_SmartEntityBehaviorTag, S_SmartObjectBehaviorTagContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_SmartObjectBehaviorTag;
    uint8_t _ownState[0x10];   // [UNVERIFIED] own members above C_SmartEntityBehaviorTag (0x28)
};
static_assert(sizeof(C_SmartObjectBehaviorTag) == 0x38);

}  // namespace wh::xgenaimodule::BehaviorTree
