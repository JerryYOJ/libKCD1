#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_LinkFilterNoSource.h"
#include "../C_Node.h"
#include "C_LinkAllData.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <LinkDataFilter>.

namespace wh::xgenaimodule::BehaviorTree {

// <LinkDataFilter>  RTTI C_LinkDataFilter  vtable 0x1821dbc18  size 0x30  base C_LinkFilterNoSource<C_LinkDataFilter, C_LinkAllData<C_Node>>  ctx S_LinkDataFilterContext
struct S_LinkDataFilterContext;
class C_LinkDataFilter : public C_NodeWrapper<C_LinkDataFilter, C_LinkFilterNoSource<C_LinkDataFilter, C_LinkAllData<C_Node>>, S_LinkDataFilterContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_LinkDataFilter;
    uint8_t _ownState[0x8];   // [UNVERIFIED] own members above C_LinkFilterNoSource<C_LinkDataFilter, C_LinkAllData<C_Node>> (0x28)
};
static_assert(sizeof(C_LinkDataFilter) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
