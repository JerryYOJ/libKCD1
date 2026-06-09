#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_ActiveBarrier.h"

// C_NpcStateGateBase - intermediate BT node base.

namespace wh::xgenaimodule::BehaviorTree {

// C_NpcStateGateBase : public C_ActiveBarrier   (RTTI-confirmed intermediate base; modeled THIN,
//  own members [UNVERIFIED] absorbed into deriving node size.)
class C_NpcStateGateBase : public C_ActiveBarrier {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_NpcStateGateBase;
};

}  // namespace wh::xgenaimodule::BehaviorTree
