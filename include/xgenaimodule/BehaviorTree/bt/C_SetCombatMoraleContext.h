#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "C_ModifyMoraleContextBase.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <SetCombatMoraleContext>.

namespace wh::xgenaimodule::BehaviorTree {

// <SetCombatMoraleContext>  RTTI C_SetCombatMoraleContext  vtable 0x182210368  size 0x28  base C_ModifyMoraleContextBase  ctx S_ModifyMoraleContextBaseContext
struct S_ModifyMoraleContextBaseContext;
class C_SetCombatMoraleContext : public C_NodeWrapper<C_SetCombatMoraleContext, C_ModifyMoraleContextBase, S_ModifyMoraleContextBaseContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_SetCombatMoraleContext;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_SetCombatMoraleContext) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
