#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_LinkFilterWithSource.h"
#include "../C_Node.h"
#include "C_LinkLimitedData.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <AreaContainsFilter>.

namespace wh::xgenaimodule::BehaviorTree {

// <AreaContainsFilter>  RTTI C_AreaContainsFilter  vtable 0x1826ff5e8  size 0x30  base C_LinkFilterWithSource<C_AreaContainsFilter, C_LinkLimitedData<C_Node>>  ctx S_AreaContainsFilterContext
struct S_AreaContainsFilterContext;
class C_AreaContainsFilter : public C_NodeWrapper<C_AreaContainsFilter, C_LinkFilterWithSource<C_AreaContainsFilter, C_LinkLimitedData<C_Node>>, S_AreaContainsFilterContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_AreaContainsFilter;
    uint8_t _ownState[0x8];   // [UNVERIFIED] own members above C_LinkFilterWithSource<C_AreaContainsFilter, C_LinkLimitedData<C_Node>> (0x28)
};
static_assert(sizeof(C_AreaContainsFilter) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
