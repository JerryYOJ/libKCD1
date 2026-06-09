#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_DefferedStateChange.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <StealthAccept>.

namespace wh::xgenaimodule::BehaviorTree {

// <StealthAccept>  RTTI C_StealthAccept  vtable 0x1823505f8  size 0x28  base C_DefferedStateChange  ctx S_StealthAcceptContext
struct S_StealthAcceptContext;
class C_StealthAccept : public C_NodeWrapper<C_StealthAccept, C_DefferedStateChange, S_StealthAcceptContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_StealthAccept;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_StealthAccept) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
