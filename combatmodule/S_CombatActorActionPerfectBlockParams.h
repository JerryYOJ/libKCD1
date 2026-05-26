#pragma once

#include <cstdint>
#include "I_CombatActorActionParamsReflect.h"

namespace wh::combatmodule {

// Vtable: 0x1821B4198 (primary), 0x1821B40C0 (reflect at +0x08)
struct S_CombatActorActionPerfectBlockParams : public I_CombatActorActionParamsReflect {
    ~S_CombatActorActionPerfectBlockParams() override = default;
    I_CombatActorActionParamsReflect m_reflect; // +0x08  embedded reflection vtable
    uint64_t m_data;            // +0x10  (init 0)
    uint16_t m_flags;           // +0x18  (init 0x100)
    uint8_t  _pad1A[6];         // +0x1A
    uint64_t m_data2;           // +0x20  (init 0)
};
static_assert(sizeof(S_CombatActorActionPerfectBlockParams) == 0x28);

}  // namespace wh::combatmodule
