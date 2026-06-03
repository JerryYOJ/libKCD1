#pragma once

#include <cstdint>
#include "bt_tags.h"

// C_LinkModifier - template BT node base family.

namespace wh::xgenaimodule::BehaviorTree {

// template C_LinkModifier<class TData, class ISorter> : public TData, public I_LinkFilter
// (RTTI-confirmed family; modeled THIN, own members [UNVERIFIED] absorbed
//  into each deriving node's size.)
template<class TData, class ISorter>
class C_LinkModifier : public TData, public I_LinkFilter {};

}  // namespace wh::xgenaimodule::BehaviorTree
