#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Decorator.h"

// C_ForBase - intermediate BT node base.

namespace wh::xgenaimodule::BehaviorTree {

// C_ForBase : public C_Decorator   (RTTI-confirmed intermediate base; modeled THIN,
//  own members [UNVERIFIED] absorbed into deriving node size.)
class C_ForBase : public C_Decorator {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_ForBase;
};

}  // namespace wh::xgenaimodule::BehaviorTree
