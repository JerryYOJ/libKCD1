#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <GetDynamicInformationValue>.

namespace wh::xgenaimodule::BehaviorTree {

// <GetDynamicInformationValue>  RTTI C_GetDynamicInformationValue  vtable 0x182375710  size 0x28  base C_Node  ctx S_GetDynamicInformationValueContext
struct S_GetDynamicInformationValueContext;
class C_GetDynamicInformationValue : public C_NodeWrapper<C_GetDynamicInformationValue, C_Node, S_GetDynamicInformationValueContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_GetDynamicInformationValue;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_GetDynamicInformationValue) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
