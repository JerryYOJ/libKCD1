#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_LinkFilterWithSource.h"
#include "../C_Node.h"
#include "C_LinkLimitedData.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <WUIDFilter>.

namespace wh::xgenaimodule::BehaviorTree {

// <WUIDFilter>  RTTI C_WUIDFilter  vtable 0x1822005d8  size 0x30  base C_LinkFilterWithSource<C_WUIDFilter, C_LinkLimitedData<C_Node>>  ctx S_WUIDFilterContext
struct S_WUIDFilterContext;
class C_WUIDFilter : public C_NodeWrapper<C_WUIDFilter, C_LinkFilterWithSource<C_WUIDFilter, C_LinkLimitedData<C_Node>>, S_WUIDFilterContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_WUIDFilter;
    uint8_t _ownState[0x8];   // [UNVERIFIED] own members above C_LinkFilterWithSource<C_WUIDFilter, C_LinkLimitedData<C_Node>> (0x28)
};
static_assert(sizeof(C_WUIDFilter) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
