#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_LinkModifier.h"

// C_LyzerBase - template BT node base family.

namespace wh::xgenaimodule::BehaviorTree {

// template C_LyzerBase<class TData> : public C_LinkModifier<TData, I_LinkSorter>
// (RTTI-confirmed family; modeled THIN, own members [UNVERIFIED] absorbed
//  into each deriving node's size.)
template<class TData>
class C_LyzerBase : public C_LinkModifier<TData, I_LinkSorter> {};

}  // namespace wh::xgenaimodule::BehaviorTree
