#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <DisableLink>.

namespace wh::xgenaimodule::BehaviorTree {

// <DisableLink>  RTTI C_DisableLink  vtable 0x182373df0  size 0x28  base C_Node  ctx S_DisableLinkContext
struct S_DisableLinkContext;
class C_DisableLink : public C_NodeWrapper<C_DisableLink, C_Node, S_DisableLinkContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_DisableLink;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_DisableLink) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
