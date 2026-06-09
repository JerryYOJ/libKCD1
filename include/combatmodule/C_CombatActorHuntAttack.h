#pragma once

#include <cstdint>
#include "C_CombatActorObject.h"
#include "../Offsets/Offsets_VTABLE.h"

namespace wh::combatmodule {

// ---------------------------------------------------------------------------
// I_CombatActorHuntAttack — secondary MI interface for hunt attack dispatch.
//
// RTTI: .?AVI_CombatActorHuntAttack@combatmodule@wh@@
// Vtable: WHGame+0x21CB3B8 (3 slots)
// Embedded at +0x10 within C_CombatActorHuntAttack (MI offset=0x10).
// ---------------------------------------------------------------------------
// VERIFIED from Request (sub_18063A428): `if (result != 2) return 0`
// and TryHuntAttack debug path: `return 2` when forced.
enum class E_HuntAttackResult : int {
    Blocked  = 0,   // capability/perk 0x2C missing
    Denied   = 1,   // target invalid or RPG roll failed
    Approved = 2,   // all checks passed — proceed with attack
};

class I_CombatActorHuntAttack {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_I_CombatActorHuntAttack;
    virtual ~I_CombatActorHuntAttack() = default;                           // [0]
    virtual E_HuntAttackResult TryHuntAttack(EntityId victimEntityId) = 0; // [1] sub_180639804
    virtual E_HuntAttackResult Request(EntityId victimEntityId) = 0;     // [2] sub_18063A428
};

// ---------------------------------------------------------------------------
// C_CombatActorHuntAttack — per-actor hunt attack (tackle) subsystem.
//
// RTTI: .?AVC_CombatActorHuntAttack@combatmodule@wh@@
// Size: 0x20 bytes
// Created by sub_1805FD924, stored at C_CombatActor+0x768.
//
// MI layout:
//   +0x00: C_CombatActorObject vtable (primary, 6 slots)
//   +0x08: C_CombatActorObject::m_pOwner (C_CombatActor*)
//   +0x10: I_CombatActorHuntAttack vtable (secondary, 3 slots)
//   +0x18: m_victimEntityId — set by Request, cleared by Reset
//
// NOTE: hunt-in-progress is NOT flagged on the actor/state. The dispatched
// action is a C_CombatActorActionSyncAttack with its +0xF9 hunt-master bool set
// (sub_1806FA0C0); m_victimEntityId here is the attacker-side record.
//
// TryHuntAttack return values:
//   0 = blocked (capability missing)
//   1 = denied (target invalid or RPG roll failed)
//   2 = approved (all checks passed — speed, distance, angle, RPG)
//
// Key functions:
//   TryHuntAttack (sub_180639804):
//     Checks speed (wh_cs_HuntAttackAttackerMinLogical / VictimMinLogical),
//     distance (hunt_attack_distance table), angle (wh_cs_HuntAttackFwdAngleLimit),
//     action template (FindActionCandidate with HuntAttackMaster),
//     then calls EvaluateHuntAttackEligibility for RPG check.
//
//   EvaluateHuntAttackEligibility (sub_18063A25C):
//     Checks perk 0x2C capability, attacker-victim relationship,
//     RPG probability (sub_18047E388 type=9).
//
//   Request (sub_18063A428):
//     Actually dispatches the hunt attack. Internally re-checks
//     EvaluateHuntAttackEligibility (must return 2 to proceed).
//
// Access from C_CombatActor:
//   combatActor->vtable[0x5A]() returns I_CombatActorHuntAttack*
//   = *(combatActor + 0x768) + 0x10
// ---------------------------------------------------------------------------
class C_CombatActorHuntAttack : public C_CombatActorObject,
                                 public I_CombatActorHuntAttack {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_CombatActorHuntAttack;
    inline static constexpr auto VTABLE = Offsets::VTABLE_C_CombatActorHuntAttack;

    // C_CombatActorObject overrides (VERIFIED: GetSubsystemId=0x1C, GetName="HUNT_ATTACK")
    void Reset() override;  // sub_1806FB900: m_victimEntityId = 0
    E_CombatSubsystem GetSubsystemId() const override { return COMBAT_SUB_HUNT_ATTACK; }
    const char* GetName() const override { return "HUNT_ATTACK"; }

    // I_CombatActorHuntAttack — implemented in binary
    // ~C_CombatActorHuntAttack() override;
    // E_HuntAttackResult TryHuntAttack(EntityId victimEntityId) override;
    // E_HuntAttackResult Request(EntityId victimEntityId) override;

    EntityId m_victimEntityId;  // +0x18  entity being hunt-attacked; set by Request, cleared by Reset (primary slot [1])
    uint32_t _pad1C;            // +0x1C
};
static_assert(sizeof(C_CombatActorHuntAttack) == 0x20);

}  // namespace wh::combatmodule
