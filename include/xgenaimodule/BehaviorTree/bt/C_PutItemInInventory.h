#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_AnimatedAction.h"
#include "C_InstantPutItemInInventory.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <PutItemInInventory>.

namespace wh::xgenaimodule::BehaviorTree {

// <PutItemInInventory>  RTTI C_PutItemInInventory  vtable 0x182333730  size 0x28  base C_InstantPutItemInInventory<C_AnimatedAction<C_PutItemAnimAction>>  ctx S_BaseNodeContext
class C_PutItemInInventory : public C_NodeWrapper<C_PutItemInInventory, C_InstantPutItemInInventory<C_AnimatedAction<C_PutItemAnimAction>>, S_BaseNodeContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_PutItemInInventory;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_PutItemInInventory) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
