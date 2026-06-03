#pragma once

#include <cstdint>
#include "bt_tags.h"

// C_GraphSearchFilterBase - template BT node base family.

namespace wh::xgenaimodule::BehaviorTree {

// template C_GraphSearchFilterBase<class TFilter, class TBase> : public TBase, public I_LinkFilter
// (RTTI-confirmed family; modeled THIN, own members [UNVERIFIED] absorbed
//  into each deriving node's size.)
template<class TFilter, class TBase>
class C_GraphSearchFilterBase : public TBase, public I_LinkFilter {};

}  // namespace wh::xgenaimodule::BehaviorTree
