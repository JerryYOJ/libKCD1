#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"

// C_ChangeAreaLabel - intermediate BT node base.

namespace wh::xgenaimodule::BehaviorTree {

// C_ChangeAreaLabel : public C_Node   (RTTI-confirmed intermediate base; modeled THIN,
//  own members [UNVERIFIED] absorbed into deriving node size.)
class C_ChangeAreaLabel : public C_Node {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_ChangeAreaLabel;
};

}  // namespace wh::xgenaimodule::BehaviorTree
