#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Barrier.h"

// C_ActiveBarrier - intermediate BT node base.

namespace wh::xgenaimodule::BehaviorTree {

// C_ActiveBarrier : public C_ExecutionBarrier   (RTTI-confirmed intermediate base; modeled THIN,
//  own members [UNVERIFIED] absorbed into deriving node size.)
class C_ActiveBarrier : public C_ExecutionBarrier {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_ActiveBarrier;
};

}  // namespace wh::xgenaimodule::BehaviorTree
