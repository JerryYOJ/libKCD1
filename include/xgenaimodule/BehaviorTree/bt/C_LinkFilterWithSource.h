#pragma once

#include <cstdint>
#include "bt_tags.h"

// C_LinkFilterWithSource - template BT node base family.

namespace wh::xgenaimodule::BehaviorTree {

// template C_LinkFilterWithSource<class TFilter, class TData> : public TData, public I_LinkFilter
// (RTTI-confirmed family; modeled THIN, own members [UNVERIFIED] absorbed
//  into each deriving node's size.)
template<class TFilter, class TData>
class C_LinkFilterWithSource : public TData, public I_LinkFilter {};

}  // namespace wh::xgenaimodule::BehaviorTree
