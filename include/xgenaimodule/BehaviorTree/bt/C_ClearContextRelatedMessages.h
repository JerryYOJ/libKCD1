#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <ClearContextRelatedMessages>.

namespace wh::xgenaimodule::BehaviorTree {

// <ClearContextRelatedMessages>  RTTI C_ClearContextRelatedMessages  vtable 0x18231cd70  size 0x28  base C_Node  ctx S_BaseNodeContext
class C_ClearContextRelatedMessages : public C_NodeWrapper<C_ClearContextRelatedMessages, C_Node, S_BaseNodeContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_ClearContextRelatedMessages;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_ClearContextRelatedMessages) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
