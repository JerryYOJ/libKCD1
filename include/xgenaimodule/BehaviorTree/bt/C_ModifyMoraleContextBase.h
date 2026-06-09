#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"

// C_ModifyMoraleContextBase - intermediate BT node base.

namespace wh::xgenaimodule::BehaviorTree {

// C_ModifyMoraleContextBase : public C_Node   (RTTI-confirmed intermediate base; modeled THIN,
//  own members [UNVERIFIED] absorbed into deriving node size.)
class C_ModifyMoraleContextBase : public C_Node {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_ModifyMoraleContextBase;
};

}  // namespace wh::xgenaimodule::BehaviorTree
