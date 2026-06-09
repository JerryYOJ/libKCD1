#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <TransferInformation>.

namespace wh::xgenaimodule::BehaviorTree {

// <TransferInformation>  RTTI C_TransferInformation  vtable 0x182374dd8  size 0x28  base C_Node  ctx S_TransferInformationContext
struct S_TransferInformationContext;
class C_TransferInformation : public C_NodeWrapper<C_TransferInformation, C_Node, S_TransferInformationContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_TransferInformation;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_TransferInformation) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
