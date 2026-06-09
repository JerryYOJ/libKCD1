#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_LinkFilterWithSource.h"
#include "../C_Node.h"
#include "C_LinkLimitedData.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <ItemParamFilter>.

namespace wh::xgenaimodule::BehaviorTree {

// <ItemParamFilter>  RTTI C_ItemParamFilter  vtable 0x18220d2f0  size 0x30  base C_LinkFilterWithSource<C_ItemParamFilter, C_LinkLimitedData<C_Node>>  ctx S_ItemParamFilterContext
struct S_ItemParamFilterContext;
class C_ItemParamFilter : public C_NodeWrapper<C_ItemParamFilter, C_LinkFilterWithSource<C_ItemParamFilter, C_LinkLimitedData<C_Node>>, S_ItemParamFilterContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_ItemParamFilter;
    uint8_t _ownState[0x8];   // [UNVERIFIED] own members above C_LinkFilterWithSource<C_ItemParamFilter, C_LinkLimitedData<C_Node>> (0x28)
};
static_assert(sizeof(C_ItemParamFilter) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
