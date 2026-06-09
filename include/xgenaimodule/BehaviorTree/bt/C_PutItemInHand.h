#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_AnimatedAction.h"
#include "C_InstantPutItemInHand.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <PutItemInHand>.

namespace wh::xgenaimodule::BehaviorTree {

// <PutItemInHand>  RTTI C_PutItemInHand  vtable 0x182333a18  size 0x28  base C_InstantPutItemInHand<C_AnimatedAction<C_PutItemInHandAnimAction>>  ctx S_BaseNodeContext
class C_PutItemInHand : public C_NodeWrapper<C_PutItemInHand, C_InstantPutItemInHand<C_AnimatedAction<C_PutItemInHandAnimAction>>, S_BaseNodeContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_PutItemInHand;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_PutItemInHand) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
