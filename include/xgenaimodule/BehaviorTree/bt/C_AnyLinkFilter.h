#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_LinkFilterWithSource.h"
#include "../C_Node.h"
#include "C_LinkLimitedData.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <AnyLinkFilter>.

namespace wh::xgenaimodule::BehaviorTree {

// <AnyLinkFilter>  RTTI C_AnyLinkFilter  vtable 0x1821fca00  size 0x30  base C_LinkFilterWithSource<C_AnyLinkFilter, C_LinkLimitedData<C_Node>>  ctx S_AnyLinkFilterContext
struct S_AnyLinkFilterContext;
class C_AnyLinkFilter : public C_NodeWrapper<C_AnyLinkFilter, C_LinkFilterWithSource<C_AnyLinkFilter, C_LinkLimitedData<C_Node>>, S_AnyLinkFilterContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_AnyLinkFilter;
    uint8_t _ownState[0x8];   // [UNVERIFIED] own members above C_LinkFilterWithSource<C_AnyLinkFilter, C_LinkLimitedData<C_Node>> (0x28)
};
static_assert(sizeof(C_AnyLinkFilter) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
