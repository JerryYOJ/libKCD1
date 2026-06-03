#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_SmartEntityBehaviorTag.h"

// C_BehaviorAdopter - intermediate BT node base.

namespace wh::xgenaimodule::BehaviorTree {

// C_BehaviorAdopter : public C_SmartEntityBehaviorTag   (RTTI-confirmed intermediate base; modeled THIN,
//  own members [UNVERIFIED] absorbed into deriving node size.)
class C_BehaviorAdopter : public C_SmartEntityBehaviorTag {};

}  // namespace wh::xgenaimodule::BehaviorTree
