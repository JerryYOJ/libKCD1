#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Gate.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <IsWeaponDrawn>.

namespace wh::xgenaimodule::BehaviorTree {

// <IsWeaponDrawn>  RTTI C_IsWeaponDrawn  vtable 0x1823347d0  size 0x68  base C_Gate  ctx S_IsWeaponDrawnContext
struct S_IsWeaponDrawnContext;
class C_IsWeaponDrawn : public C_NodeWrapper<C_IsWeaponDrawn, C_Gate, S_IsWeaponDrawnContext>
{
    // no own data members (object == 0x68)
};
static_assert(sizeof(C_IsWeaponDrawn) == 0x68);

}  // namespace wh::xgenaimodule::BehaviorTree
