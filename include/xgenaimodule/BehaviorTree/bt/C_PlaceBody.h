#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_DefferedStateChange.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <PlaceBody>.

namespace wh::xgenaimodule::BehaviorTree {

// <PlaceBody>  RTTI C_PlaceBody  vtable 0x18233f068  size 0x28  base C_DefferedStateChange  ctx S_PlaceBodyContext
struct S_PlaceBodyContext;
class C_PlaceBody : public C_NodeWrapper<C_PlaceBody, C_DefferedStateChange, S_PlaceBodyContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_PlaceBody;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_PlaceBody) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
