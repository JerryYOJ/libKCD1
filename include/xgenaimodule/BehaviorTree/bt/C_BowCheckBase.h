#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"

// C_BowCheckBase - intermediate BT node base.

namespace wh::xgenaimodule::BehaviorTree {

// C_BowCheckBase : public C_Node   (RTTI-confirmed intermediate base; modeled THIN,
//  own members [UNVERIFIED] absorbed into deriving node size.)
class C_BowCheckBase : public C_Node {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_BowCheckBase;
};

}  // namespace wh::xgenaimodule::BehaviorTree
