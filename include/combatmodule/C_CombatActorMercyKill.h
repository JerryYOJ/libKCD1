#pragma once

#include <cstdint>
#include "C_CombatActorObject.h"
#include "../Offsets/Offsets_VTABLE.h"

namespace wh::combatmodule {

// ---------------------------------------------------------------------------
// I_CombatActorMercyKill — secondary MI interface for mercy-kill dispatch.
//
// RTTI: .?AVI_CombatActorMercyKill@combatmodule@wh@@
// Vtable: WHGame+0x21CB410 (3 slots)
// Embedded at +0x10 within C_CombatActorMercyKill (MI offset=0x10).
//
// Same "victim-targeted action" shape as I_CombatActorHuntAttack /
// I_CombatActorHorsePullDown: [0] dtor, [1] Can (tri-state), [2] Request (dispatch).
// ---------------------------------------------------------------------------
class I_CombatActorMercyKill {
public:
    virtual ~I_CombatActorMercyKill() = default;                    // [0]
    virtual int CanMercyKill(EntityId victimEntityId) = 0;          // [1] sub_180F50784
    virtual bool RequestMercyKill(EntityId victimEntityId) = 0;     // [2] sub_180F537E0
};

// ---------------------------------------------------------------------------
// C_CombatActorMercyKill — per-actor mercy-kill (finisher) subsystem.
//
// RTTI: .?AVC_CombatActorMercyKill@combatmodule@wh@@
// Size: 0x20 bytes
// Created by sub_1805FD8B8, stored at C_CombatActor+0x760.
// Subsystem ID: 0x1D (COMBAT_SUB_MERCY_KILL), name "MERCY_KILL".
//
// The ctor also connects a (nop) callback to the combat state signal at
// state+0x4B8.
//
// MI layout (same as HuntAttack/HorsePullDown):
//   +0x00: C_CombatActorObject vtable (primary, WHGame+0x21CB3D8)
//   +0x08: C_CombatActorObject::m_pOwner (C_CombatActor*)
//   +0x10: I_CombatActorMercyKill vtable (secondary, WHGame+0x21CB410)
//   +0x18: uint32 state (zeroed by Reset)
//   +0x1C: padding
//
// CanMercyKill (sub_180F50784) returns:
//   0 = blocked (target invalid / not dead-or-unconscious / no action template)
//   1 = eligible
//   2 = approved (relationship + RPG roll via sub_18047E388 type=9 passed)
//   Note: RequestMercyKill (sub_180F537E0) does NOT re-check eligibility — it
//   dispatches directly (unlike HuntAttack/HorsePullDown which require == 2).
// ---------------------------------------------------------------------------
class C_CombatActorMercyKill : public C_CombatActorObject,
                                public I_CombatActorMercyKill {
public:
    inline static constexpr auto VTABLE = Offsets::VTABLE_C_CombatActorMercyKill;

    E_CombatSubsystem GetSubsystemId() const override { return COMBAT_SUB_MERCY_KILL; }
    const char* GetName() const override { return "MERCY_KILL"; }

    // I_CombatActorMercyKill — implemented in binary
    // int CanMercyKill(EntityId victimEntityId) override;     // sub_180F50784
    // bool RequestMercyKill(EntityId victimEntityId) override; // sub_180F537E0

    uint32_t m_state18;     // +0x18  (zeroed by Reset, slot [1])
    uint32_t _pad1C;        // +0x1C
};
static_assert(sizeof(C_CombatActorMercyKill) == 0x20);

}  // namespace wh::combatmodule
