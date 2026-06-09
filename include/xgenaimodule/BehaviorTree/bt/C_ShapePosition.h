#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_DefferedStateChange.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <ShapePosition>.

namespace wh::xgenaimodule::BehaviorTree {

// <ShapePosition>  RTTI C_ShapePosition  vtable 0x1823495d8  size 0x28  base C_DefferedStateChange  ctx S_ShapePositionContext
struct S_ShapePositionContext;
class C_ShapePosition : public C_NodeWrapper<C_ShapePosition, C_DefferedStateChange, S_ShapePositionContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_ShapePosition;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_ShapePosition) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
