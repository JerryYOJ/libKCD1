#pragma once

#include <cstdint>
#include "bt_tags.h"
#include "../C_Node.h"
#include "../C_NodeWrapper.h"
#include "../C_NodeContext.h"

// BT node <ProduceSound>.

namespace wh::xgenaimodule::BehaviorTree {

// <ProduceSound>  RTTI C_ProduceSound  vtable 0x18233d388  size 0x28  base C_Node  ctx S_ProduceSoundContext
struct S_ProduceSoundContext;
class C_ProduceSound : public C_NodeWrapper<C_ProduceSound, C_Node, S_ProduceSoundContext>
{
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_ProduceSound;
    // no own data members (object == 0x28)
};
static_assert(sizeof(C_ProduceSound) == 0x28);

}  // namespace wh::xgenaimodule::BehaviorTree
