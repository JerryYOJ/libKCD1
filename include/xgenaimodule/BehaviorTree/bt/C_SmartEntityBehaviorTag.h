#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_ForwardingData.h"
#include "C_BehaviorTag.h"

// C_SmartEntityBehaviorTag - intermediate BT node base.

namespace wh::xgenaimodule::BehaviorTree {

// C_SmartEntityBehaviorTag : public C_ForwardingData<C_BehaviorTag>   (RTTI-confirmed intermediate base; modeled THIN,
//  own members [UNVERIFIED] absorbed into deriving node size.)
class C_SmartEntityBehaviorTag : public C_ForwardingData<C_BehaviorTag> {};

}  // namespace wh::xgenaimodule::BehaviorTree
