#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Composite.h"

// C_FilterOperation - template BT node base family.

namespace wh::xgenaimodule::BehaviorTree {

// template C_FilterOperation<class TPolicy> : public C_Composite
// (RTTI family; every instantiation is a 0x60 node = base 0x40 +
//  0x20 own state. Own members [UNVERIFIED]; padded so sizeof matches.)
template<class TPolicy>
class C_FilterOperation : public C_Composite { uint8_t _ownState[0x20]; };

}  // namespace wh::xgenaimodule::BehaviorTree
