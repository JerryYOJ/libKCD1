#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <ClearDynamicInformationValue>.

namespace wh::xgenaimodule::BehaviorTree {

// <ClearDynamicInformationValue>  RTTI C_ClearDynamicInformationValue  vtable 0x182376a88  size 0x28  base C_Node  ctx S_ClearDynamicInformationValueContext
struct S_ClearDynamicInformationValueContext;
class C_ClearDynamicInformationValue : public C_NodeWrapper<C_ClearDynamicInformationValue, C_Node, S_ClearDynamicInformationValueContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_ClearDynamicInformationValue;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_ClearDynamicInformationValue) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
