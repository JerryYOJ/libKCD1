#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"

// C_MakeIdleBase - intermediate BT node base.

namespace wh::xgenaimodule::BehaviorTree {

// C_MakeIdleBase : public C_Node   (RTTI-confirmed intermediate base; modeled THIN,
//  own members [UNVERIFIED] absorbed into deriving node size.)
class C_MakeIdleBase : public C_Node {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_MakeIdleBase;
};

}  // namespace wh::xgenaimodule::BehaviorTree
