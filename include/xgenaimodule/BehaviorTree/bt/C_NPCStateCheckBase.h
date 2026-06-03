#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Gate.h"

// C_NPCStateCheckBase - intermediate BT node base.

namespace wh::xgenaimodule::BehaviorTree {

// C_NPCStateCheckBase : public C_Gate   (RTTI-confirmed intermediate base; modeled THIN,
//  own members [UNVERIFIED] absorbed into deriving node size.)
class C_NPCStateCheckBase : public C_Gate {};

}  // namespace wh::xgenaimodule::BehaviorTree
