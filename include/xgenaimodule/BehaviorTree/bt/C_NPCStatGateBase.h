#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_ActiveBarrier.h"

// C_NPCStatGateBase - intermediate BT node base.

namespace wh::xgenaimodule::BehaviorTree {

// C_NPCStatGateBase : public C_ActiveBarrier   (RTTI-confirmed intermediate base; modeled THIN,
//  own members [UNVERIFIED] absorbed into deriving node size.)
class C_NPCStatGateBase : public C_ActiveBarrier {};

}  // namespace wh::xgenaimodule::BehaviorTree
