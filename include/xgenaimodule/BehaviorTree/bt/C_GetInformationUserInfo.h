#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <GetInformationUserInfo>.

namespace wh::xgenaimodule::BehaviorTree {

// <GetInformationUserInfo>  RTTI C_GetInformationUserInfo  vtable 0x1823755b8  size 0x28  base C_Node  ctx S_GetInformationUserInfoContext
struct S_GetInformationUserInfoContext;
class C_GetInformationUserInfo : public C_NodeWrapper<C_GetInformationUserInfo, C_Node, S_GetInformationUserInfoContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_GetInformationUserInfo;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_GetInformationUserInfo) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
