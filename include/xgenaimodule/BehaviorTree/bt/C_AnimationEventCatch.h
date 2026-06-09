#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Composite.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <AnimationEventCatch>.

namespace wh::xgenaimodule::BehaviorTree {

// <AnimationEventCatch>  RTTI C_AnimationEventCatch  vtable 0x1821d43c8  size 0x58  base C_FixedComposite<2>  ctx S_AnimationEventCatchContext
struct S_AnimationEventCatchContext;
class C_AnimationEventCatch : public C_NodeWrapper<C_AnimationEventCatch, C_FixedComposite<2>, S_AnimationEventCatchContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_AnimationEventCatch;
    uint8_t _ownState[0x20];   // [UNVERIFIED] own members above C_FixedComposite<2> (0x38)
};
static_assert(sizeof(C_AnimationEventCatch) == 0x58);

}  // namespace wh::xgenaimodule::BehaviorTree
