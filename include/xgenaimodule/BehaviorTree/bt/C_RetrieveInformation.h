#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <RetrieveInformation>.

namespace wh::xgenaimodule::BehaviorTree {

// <RetrieveInformation>  RTTI C_RetrieveInformation  vtable 0x182220650  size 0x28  base C_Node  ctx S_RetrieveInformationContext
struct S_RetrieveInformationContext;
class C_RetrieveInformation : public C_NodeWrapper<C_RetrieveInformation, C_Node, S_RetrieveInformationContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_RetrieveInformation;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_RetrieveInformation) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
