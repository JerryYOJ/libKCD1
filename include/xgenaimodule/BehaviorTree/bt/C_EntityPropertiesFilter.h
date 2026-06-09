#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_LinkFilterWithSource.h"
#include "../C_Node.h"
#include "C_LinkLimitedData.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <EntityPropertiesFilter>.

namespace wh::xgenaimodule::BehaviorTree {

// <EntityPropertiesFilter>  RTTI C_EntityPropertiesFilter  vtable 0x1826ff2e0  size 0x30  base C_LinkFilterWithSource<C_EntityPropertiesFilter, C_LinkLimitedData<C_Node>>  ctx S_EntityPropertiesFilterContext
struct S_EntityPropertiesFilterContext;
class C_EntityPropertiesFilter : public C_NodeWrapper<C_EntityPropertiesFilter, C_LinkFilterWithSource<C_EntityPropertiesFilter, C_LinkLimitedData<C_Node>>, S_EntityPropertiesFilterContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_EntityPropertiesFilter;
    uint8_t _ownState[0x8];   // [UNVERIFIED] own members above C_LinkFilterWithSource<C_EntityPropertiesFilter, C_LinkLimitedData<C_Node>> (0x28)
};
static_assert(sizeof(C_EntityPropertiesFilter) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
