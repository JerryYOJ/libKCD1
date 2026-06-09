#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <SpreadInformation>.

namespace wh::xgenaimodule::BehaviorTree {

// <SpreadInformation>  RTTI C_SpreadInformation  vtable 0x182374360  size 0x28  base C_Node  ctx S_SpreadInformationContext
struct S_SpreadInformationContext;
class C_SpreadInformation : public C_NodeWrapper<C_SpreadInformation, C_Node, S_SpreadInformationContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_SpreadInformation;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_SpreadInformation) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
