#pragma once

#include <cstdint>
#include "bt_tags.h"

// C_LinkNoData - template BT node base family.

namespace wh::xgenaimodule::BehaviorTree {

// template C_LinkNoData<class T> : public T
// (RTTI-confirmed family; modeled THIN, own members [UNVERIFIED] absorbed
//  into each deriving node's size.)
template<class T>
class C_LinkNoData : public T {};

}  // namespace wh::xgenaimodule::BehaviorTree
