#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <RandDistribution>.

namespace wh::xgenaimodule::BehaviorTree {

// <RandDistribution>  RTTI C_RandDistribution  vtable 0x18233c1f0  size 0x28  base C_Node  ctx S_RandDistributionContext
struct S_RandDistributionContext;
class C_RandDistribution : public C_NodeWrapper<C_RandDistribution, C_Node, S_RandDistributionContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_RandDistribution;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_RandDistribution) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
