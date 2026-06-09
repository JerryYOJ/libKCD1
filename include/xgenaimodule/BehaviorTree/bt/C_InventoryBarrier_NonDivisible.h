#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_DeferredExecution.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <InventoryBarrier_NonDivisible>.

namespace wh::xgenaimodule::BehaviorTree {

// <InventoryBarrier_NonDivisible>  RTTI C_InventoryBarrier_NonDivisible  vtable 0x18235c998  size 0x30  base C_DeferredExecution  ctx S_InventoryBarrier_NonDivisibleContext
struct S_InventoryBarrier_NonDivisibleContext;
class C_InventoryBarrier_NonDivisible : public C_NodeWrapper<C_InventoryBarrier_NonDivisible, C_DeferredExecution, S_InventoryBarrier_NonDivisibleContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_InventoryBarrier_NonDivisible;
    // no own data members (object == 0x30)
};
static_assert(sizeof(C_InventoryBarrier_NonDivisible) == 0x30);

}  // namespace wh::xgenaimodule::BehaviorTree
