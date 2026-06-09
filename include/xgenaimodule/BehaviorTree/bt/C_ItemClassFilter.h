#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_LinkFilterWithSource.h"
#include "../C_Node.h"
#include "C_LinkLimitedData.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <ItemClassFilter>.

namespace wh::xgenaimodule::BehaviorTree {

// <ItemClassFilter>  RTTI C_ItemClassFilter  vtable 0x1821dfcd0  size 0x30  base C_LinkFilterWithSource<C_ItemClassFilter, C_LinkLimitedData<C_Node>>  ctx S_ItemClassFilterContext
struct S_ItemClassFilterContext;
class C_ItemClassFilter : public C_NodeWrapper<C_ItemClassFilter, C_LinkFilterWithSource<C_ItemClassFilter, C_LinkLimitedData<C_Node>>, S_ItemClassFilterContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_ItemClassFilter;
    uint8_t _ownState[0x8];   // [UNVERIFIED] own members above C_LinkFilterWithSource<C_ItemClassFilter, C_LinkLimitedData<C_Node>> (0x28)
};
static_assert(sizeof(C_ItemClassFilter) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
