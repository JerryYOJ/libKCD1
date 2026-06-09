#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_GraphSearchFilterBase.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <Gen2EntityClassFilter>.

namespace wh::xgenaimodule::BehaviorTree {

// <Gen2EntityClassFilter>  RTTI C_Gen2EntityClassFilter  vtable 0x1826fe0e0  size 0x30  base C_GraphSearchFilterBase<C_Gen2EntityClassFilter, C_Node>  ctx S_Gen2EntityClassFilterContext
struct S_Gen2EntityClassFilterContext;
class C_Gen2EntityClassFilter : public C_NodeWrapper<C_Gen2EntityClassFilter, C_GraphSearchFilterBase<C_Gen2EntityClassFilter, C_Node>, S_Gen2EntityClassFilterContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_Gen2EntityClassFilter;
    uint8_t _ownState[0x8];   // [UNVERIFIED] own members above C_GraphSearchFilterBase<C_Gen2EntityClassFilter, C_Node> (0x28)
};
static_assert(sizeof(C_Gen2EntityClassFilter) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
