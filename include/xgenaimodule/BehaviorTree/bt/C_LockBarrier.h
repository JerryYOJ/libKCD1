#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_LockNode.h"

// C_LockBarrier - template BT node base family.

namespace wh::xgenaimodule::BehaviorTree {

// template C_LockBarrier<class T> : public C_LockNode<T>
// (RTTI-confirmed family; modeled THIN, own members [UNVERIFIED] absorbed
//  into each deriving node's size.)
template<class T>
class C_LockBarrier : public C_LockNode<T> {};

}  // namespace wh::xgenaimodule::BehaviorTree
