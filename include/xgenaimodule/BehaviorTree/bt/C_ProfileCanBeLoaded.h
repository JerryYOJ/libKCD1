#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Gate.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <ProfileCanBeLoaded>.

namespace wh::xgenaimodule::BehaviorTree {

// <ProfileCanBeLoaded>  RTTI C_ProfileCanBeLoaded  vtable 0x18233c4f0  size 0x68  base C_Gate  ctx S_ProfileCanBeLoadedContext
struct S_ProfileCanBeLoadedContext;
class C_ProfileCanBeLoaded : public C_NodeWrapper<C_ProfileCanBeLoaded, C_Gate, S_ProfileCanBeLoadedContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_ProfileCanBeLoaded;
    // no own data members (object == 0x68)
};
static_assert(sizeof(C_ProfileCanBeLoaded) == 0x68);

}  // namespace wh::xgenaimodule::BehaviorTree
