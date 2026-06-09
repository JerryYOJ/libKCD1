#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_LinkFilterWithSource.h"
#include "../C_Node.h"
#include "C_LinkLimitedData.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <SlotClassFilter>.

namespace wh::xgenaimodule::BehaviorTree {

// <SlotClassFilter>  RTTI C_SlotClassFilter  vtable 0x1821e0858  size 0x30  base C_LinkFilterWithSource<C_SlotClassFilter, C_LinkLimitedData<C_Node>>  ctx S_SlotClassFilterContext
struct S_SlotClassFilterContext;
class C_SlotClassFilter : public C_NodeWrapper<C_SlotClassFilter, C_LinkFilterWithSource<C_SlotClassFilter, C_LinkLimitedData<C_Node>>, S_SlotClassFilterContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_SlotClassFilter;
    uint8_t _ownState[0x8];   // [UNVERIFIED] own members above C_LinkFilterWithSource<C_SlotClassFilter, C_LinkLimitedData<C_Node>> (0x28)
};
static_assert(sizeof(C_SlotClassFilter) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
