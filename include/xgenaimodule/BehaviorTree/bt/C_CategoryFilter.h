#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_LinkFilterWithSource.h"
#include "../C_Node.h"
#include "C_LinkLimitedData.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <CategoryFilter>.

namespace wh::xgenaimodule::BehaviorTree {

// <CategoryFilter>  RTTI C_CategoryFilter  vtable 0x1821dd860  size 0x30  base C_LinkFilterWithSource<C_CategoryFilter, C_LinkLimitedData<C_Node>>  ctx S_CategoryFilterContext
struct S_CategoryFilterContext;
class C_CategoryFilter : public C_NodeWrapper<C_CategoryFilter, C_LinkFilterWithSource<C_CategoryFilter, C_LinkLimitedData<C_Node>>, S_CategoryFilterContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_CategoryFilter;
    uint8_t _ownState[0x8];   // [UNVERIFIED] own members above C_LinkFilterWithSource<C_CategoryFilter, C_LinkLimitedData<C_Node>> (0x28)
};
static_assert(sizeof(C_CategoryFilter) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
