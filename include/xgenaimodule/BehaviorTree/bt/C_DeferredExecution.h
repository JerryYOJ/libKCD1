#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Decorator.h"

// C_DeferredExecution - intermediate BT node base.

namespace wh::xgenaimodule::BehaviorTree {

// C_DeferredExecution : public C_Decorator   (RTTI-confirmed intermediate base; modeled THIN,
//  own members [UNVERIFIED] absorbed into deriving node size.)
class C_DeferredExecution : public C_Decorator {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_DeferredExecution;
};

}  // namespace wh::xgenaimodule::BehaviorTree
