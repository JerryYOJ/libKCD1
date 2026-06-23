#pragma once

#include <cstdint>
#include "C_CombatActorUpdatedObject.h"

namespace wh::combatmodule {

// ---------------------------------------------------------------------------
// C_CombatAutomationAction -- shared base for the combat "automation" behaviours
// (defense / offense / guard / movement / ...) that live inside the per-actor
// C_CombatAutomation aggregate and drive one combat decision each tick.
//
// RTTI: .?AVC_CombatAutomationAction@combatmodule@wh@@
// vtable written by ctor sub_1805FA600(this, owner, updateFlag)
// Inherits: C_CombatActorUpdatedObject : C_CombatActorObject
// Size: 0x30 bytes
//
// (Abstract layout replica -- the C_CombatActorObject pure virtuals are left
//  inherited; instances are reached by pointer, never constructed here.)
// ---------------------------------------------------------------------------
class C_CombatAutomationAction : public C_CombatActorUpdatedObject {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_CombatAutomationAction;
    ~C_CombatAutomationAction() override = default;

    int32_t     m_flags18;          // +0x18  (init 0)
    uint32_t    _pad1C;             // +0x1C
    int64_t     m_nextActionTime;   // +0x20  earliest next-action time gate, CTimeValue ticks (init = (int64)-100000.0f = -100000; stored 8-byte via cvttss2si, NOT a float)
    uint64_t    _unk28;             // +0x28
};
static_assert(sizeof(C_CombatAutomationAction) == 0x30);

}  // namespace wh::combatmodule
