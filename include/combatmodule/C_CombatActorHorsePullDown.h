#pragma once

#include <cstdint>
#include "C_CombatActorObject.h"
#include "../Offsets/Offsets_VTABLE.h"

namespace wh::combatmodule {

// ---------------------------------------------------------------------------
// I_CombatActorHorsePullDown — secondary MI interface for horse-pulldown dispatch.
//
// RTTI: .?AVI_CombatActorHorsePullDown@combatmodule@wh@@
// Vtable: WHGame+0x21CB360 (3 slots)
// Embedded at +0x10 within C_CombatActorHorsePullDown (MI offset=0x10).
//
// Same "victim-targeted action" shape as I_CombatActorHuntAttack /
// I_CombatActorMercyKill: [0] dtor, [1] Can (tri-state), [2] Request (dispatch).
// ---------------------------------------------------------------------------
class I_CombatActorHorsePullDown {
public:
    virtual ~I_CombatActorHorsePullDown() = default;                    // [0]
    virtual int CanHorsePullDown(EntityId victimEntityId) = 0;          // [1] sub_1804563E8
    virtual bool RequestHorsePullDown(EntityId victimEntityId) = 0;     // [2] sub_180461A1C
};

// ---------------------------------------------------------------------------
// C_CombatActorHorsePullDown — per-actor horse pull-down (dehorse) subsystem.
//
// RTTI: .?AVC_CombatActorHorsePullDown@combatmodule@wh@@
// Size: 0x20 bytes
// Created by sub_1805FD884, stored at C_CombatActor+0x758.
// Subsystem ID: 0x1B (COMBAT_SUB_HORSE_PULLDOWN), name "HORSE_PULLDOWN".
//
// MI layout (same as HuntAttack/MercyKill):
//   +0x00: C_CombatActorObject vtable (primary, WHGame+0x21CB328)
//   +0x08: C_CombatActorObject::m_pOwner (C_CombatActor*)
//   +0x10: I_CombatActorHorsePullDown vtable (secondary, WHGame+0x21CB360)
//   +0x18: uint32 state (zeroed by Reset)
//   +0x1C: bool flag (zeroed in ctor + Reset)
//
// CanHorsePullDown (sub_1804563E8) returns:
//   0 = blocked (target invalid / wrong mount state / distance / angle fail)
//   1 = eligible
//   2 = approved (relationship + RPG roll via sub_18047E388 type=9 passed)
//   Request requires == 2 to proceed.
// ---------------------------------------------------------------------------
class C_CombatActorHorsePullDown : public C_CombatActorObject,
                                    public I_CombatActorHorsePullDown {
public:
    inline static constexpr auto VTABLE = Offsets::VTABLE_C_CombatActorHorsePullDown;

    E_CombatSubsystem GetSubsystemId() const override { return COMBAT_SUB_HORSE_PULLDOWN; }
    const char* GetName() const override { return "HORSE_PULLDOWN"; }

    // I_CombatActorHorsePullDown — implemented in binary
    // int CanHorsePullDown(EntityId victimEntityId) override;     // sub_1804563E8
    // bool RequestHorsePullDown(EntityId victimEntityId) override; // sub_180461A1C

    uint32_t m_state18;     // +0x18  (zeroed by Reset, slot [1])
    bool     m_flag1C;      // +0x1C  (init 0)
    uint8_t  _pad1D[3];     // +0x1D
};
static_assert(sizeof(C_CombatActorHorsePullDown) == 0x20);

}  // namespace wh::combatmodule
