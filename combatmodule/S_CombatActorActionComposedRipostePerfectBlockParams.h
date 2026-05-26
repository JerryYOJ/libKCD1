#pragma once

#include <cstdint>
#include "I_CombatActorActionParamsReflect.h"

namespace wh::combatmodule {

// Vtable: 0x1821B3BC8 (primary), 0x1821B3AF0 (reflect at +0x08)
struct S_CombatActorActionComposedRipostePerfectBlockParams : public I_CombatActorActionParamsReflect {
    ~S_CombatActorActionComposedRipostePerfectBlockParams() override = default;
    I_CombatActorActionParamsReflect m_reflect; // +0x08  embedded reflection vtable
    uint64_t m_data;            // +0x10
    uint16_t m_flags;           // +0x18
    uint8_t  _pad1A[6];         // +0x1A
    uint64_t m_data2;           // +0x20
};
static_assert(sizeof(S_CombatActorActionComposedRipostePerfectBlockParams) == 0x28);

}  // namespace wh::combatmodule
