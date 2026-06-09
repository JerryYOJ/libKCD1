#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <DestroyInformationFromHolder>.

namespace wh::xgenaimodule::BehaviorTree {

// <DestroyInformationFromHolder>  RTTI C_DestroyInformationFromHolder  vtable 0x182224c98  size 0x28  base C_Node  ctx S_DestroyInformationFromHolderContext
struct S_DestroyInformationFromHolderContext;
class C_DestroyInformationFromHolder : public C_NodeWrapper<C_DestroyInformationFromHolder, C_Node, S_DestroyInformationFromHolderContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_DestroyInformationFromHolder;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_DestroyInformationFromHolder) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
