#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_LinkFilterWithSource.h"
#include "../C_Node.h"
#include "C_LinkLimitedData.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <InAreaFilter>.

namespace wh::xgenaimodule::BehaviorTree {

// <InAreaFilter>  RTTI C_InAreaFilter  vtable 0x1826fed28  size 0x30  base C_LinkFilterWithSource<C_InAreaFilter, C_LinkLimitedData<C_Node>>  ctx S_InAreaFilterContext
struct S_InAreaFilterContext;
class C_InAreaFilter : public C_NodeWrapper<C_InAreaFilter, C_LinkFilterWithSource<C_InAreaFilter, C_LinkLimitedData<C_Node>>, S_InAreaFilterContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_InAreaFilter;
    uint8_t _ownState[0x8];   // [UNVERIFIED] own members above C_LinkFilterWithSource<C_InAreaFilter, C_LinkLimitedData<C_Node>> (0x28)
};
static_assert(sizeof(C_InAreaFilter) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
