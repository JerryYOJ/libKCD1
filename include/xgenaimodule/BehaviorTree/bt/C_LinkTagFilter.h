#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "C_LinkAllData.h"
#include "C_LinkFilterNoSource.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <LinkTagFilter>.

namespace wh::xgenaimodule::BehaviorTree {

// <LinkTagFilter>  RTTI C_LinkTagFilter  vtable 0x1821dc7c8  size 0x30  base C_LinkFilterNoSource<C_LinkTagFilter, C_LinkAllData<C_Node>>  ctx S_LinkTagFilterContext
struct S_LinkTagFilterContext;
class C_LinkTagFilter : public C_NodeWrapper<C_LinkTagFilter, C_LinkFilterNoSource<C_LinkTagFilter, C_LinkAllData<C_Node>>, S_LinkTagFilterContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_LinkTagFilter;
    uint8_t _ownState[0x8];   // [UNVERIFIED] own members above C_LinkFilterNoSource<C_LinkTagFilter, C_LinkAllData<C_Node>> (0x28)
};
static_assert(sizeof(C_LinkTagFilter) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
