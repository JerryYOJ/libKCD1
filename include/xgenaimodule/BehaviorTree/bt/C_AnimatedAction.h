#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_DefferedStateChange.h"

// C_AnimatedAction - template BT node base family.

namespace wh::xgenaimodule::BehaviorTree {

// template C_AnimatedAction<class TPolicy> : public C_DefferedStateChange
// (RTTI-confirmed family; modeled THIN, own members [UNVERIFIED] absorbed
//  into each deriving node's size.)
template<class TPolicy>
class C_AnimatedAction : public C_DefferedStateChange {};

}  // namespace wh::xgenaimodule::BehaviorTree
