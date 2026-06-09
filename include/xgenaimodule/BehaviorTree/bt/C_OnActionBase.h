#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_ForwardingData.h"
#include "../C_Barrier.h"

// C_OnActionBase - intermediate BT node base.

namespace wh::xgenaimodule::BehaviorTree {

// C_OnActionBase : public C_ForwardingData<C_PassiveBarrier>   (RTTI-confirmed intermediate base; modeled THIN,
//  own members [UNVERIFIED] absorbed into deriving node size.)
class C_OnActionBase : public C_ForwardingData<C_PassiveBarrier> {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_OnActionBase;
};

}  // namespace wh::xgenaimodule::BehaviorTree
