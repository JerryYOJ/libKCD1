#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_LinkFilterWithSource.h"
#include "../C_Node.h"
#include "C_LinkLimitedData.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <EntityClassFilter>.

namespace wh::xgenaimodule::BehaviorTree {

// <EntityClassFilter>  RTTI C_EntityClassFilter  vtable 0x182202c38  size 0x30  base C_LinkFilterWithSource<C_EntityClassFilter, C_LinkLimitedData<C_Node>>  ctx S_EntityClassFilterContext
struct S_EntityClassFilterContext;
class C_EntityClassFilter : public C_NodeWrapper<C_EntityClassFilter, C_LinkFilterWithSource<C_EntityClassFilter, C_LinkLimitedData<C_Node>>, S_EntityClassFilterContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_EntityClassFilter;
    uint8_t _ownState[0x8];   // [UNVERIFIED] own members above C_LinkFilterWithSource<C_EntityClassFilter, C_LinkLimitedData<C_Node>> (0x28)
};
static_assert(sizeof(C_EntityClassFilter) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
