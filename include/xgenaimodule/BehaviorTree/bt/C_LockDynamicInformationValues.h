#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Decorator.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <LockDynamicInformationValues>.

namespace wh::xgenaimodule::BehaviorTree {

// <LockDynamicInformationValues>  RTTI C_LockDynamicInformationValues  vtable 0x182222f40  size 0x30  base C_Decorator  ctx S_LockDynamicInformationValuesContext
struct S_LockDynamicInformationValuesContext;
class C_LockDynamicInformationValues : public C_NodeWrapper<C_LockDynamicInformationValues, C_Decorator, S_LockDynamicInformationValuesContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_LockDynamicInformationValues;
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_LockDynamicInformationValues) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
