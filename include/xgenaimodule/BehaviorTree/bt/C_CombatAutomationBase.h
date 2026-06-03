#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_CombatNode.h"

// C_CombatAutomationBase - template BT node base family.

namespace wh::xgenaimodule::BehaviorTree {

// template C_CombatAutomationBase<class T> : public C_CombatNode<T>
// (RTTI-confirmed family; modeled THIN, own members [UNVERIFIED] absorbed
//  into each deriving node's size.)
template<class T>
class C_CombatAutomationBase : public C_CombatNode<T> {};

}  // namespace wh::xgenaimodule::BehaviorTree
