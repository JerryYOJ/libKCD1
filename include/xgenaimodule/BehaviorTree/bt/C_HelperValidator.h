#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <HelperValidator>.

namespace wh::xgenaimodule::BehaviorTree {

// <HelperValidator>  RTTI C_HelperValidator  vtable 0x18232bb28  size 0x28  base C_Node  ctx S_HelperValidatorContext
struct S_HelperValidatorContext;
class C_HelperValidator : public C_NodeWrapper<C_HelperValidator, C_Node, S_HelperValidatorContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_HelperValidator;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_HelperValidator) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
