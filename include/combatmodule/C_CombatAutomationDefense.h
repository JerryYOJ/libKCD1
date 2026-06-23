#pragma once

#include <cstdint>
#include "C_CombatAutomationAction.h"
#include "S_ReactionWeights.h"

namespace wh::combatmodule {

// ---------------------------------------------------------------------------
// C_CombatAutomationDefense -- the per-actor melee-defense "brain". Each defense
// tick it picks ONE reaction (no-op / normal block / perfect block / master
// strike / dodge) by a weighted-random draw, then dispatches it. This is the
// native node behind the <MeleeDefenseAutomation/> BT leaf; it owns the
// reaction-weight override that <MeleeDefenseAutomationControls/> writes.
//
// RTTI: .?AVC_CombatAutomationDefense@combatmodule@wh@@
// vtable @ 0x182206c48
// Constructor: sub_1806D97F4(this, owner)   [embedded at C_CombatAutomation+0x140]
// Inherits: C_CombatAutomationAction
// Size: 0x88 bytes
//
// Reaction pick (sub_1805F9408): RPG/difficulty weights come from
// C_CombatActor+0x700 (C_CombatRPG) via sub_1802AE1AC; the override is overlaid
// per-slot (sub_1805FA35C: REPLACE when the slot is >= 0); then an LCG-random
// (m_rngState) cumulative selection over
// {noBlock, normalBlock, perfectBlock, specialPerfectBlock, dodge}.
//
// Reached from a combat actor as: actor->m_pAutomation->Defense()  (i.e.
// *(C_CombatActor+0x4F0)+0x140). NOTE: it is NOT at C_CombatActor+0x700 -- that
// is C_CombatRPG (the RPG weight source), a distinct object.
// ---------------------------------------------------------------------------
class C_CombatAutomationDefense : public C_CombatAutomationAction {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_C_CombatAutomationDefense;
    ~C_CombatAutomationDefense() override = default;
    void Reset() override {}                                                                 // [1] no-op stub
    E_CombatSubsystem GetSubsystemId() const override { return COMBAT_SUB_AUTOMATION_ACTION; } // [2] 0x19
    const char* GetName() const override { return "AutomationDefense"; }                     // [3] (name follows sibling pattern)

    // Install a reaction-weight override (the 5 floats are value-copied; any prior
    // override block is freed). Slots < 0 keep the RPG-computed weight; slots >= 0
    // replace it. Persists for the rest of the fight (the per-cycle automation
    // enable never touches it) until cleared or the object is rebuilt. To force a
    // defender to NEVER block / perfect-block / master-strike / dodge, pass
    // {noBlock=1, normalBlock=0, perfectBlock=0, specialPerfectBlock=0, dodge=0}.
    // sub_1804F83C8.
    void SetReactionWeights(const S_ReactionWeights& weights);

    // Drop the override; reactions revert to the RPG-computed weights. sub_1804F83C8(this, nullptr).
    void ClearReactionWeights();

    uint8_t             _selectorState[0x40];   // +0x30  reaction-selector state (init sub_1806D9860)
    uint64_t            _unk70;                 // +0x70
    S_ReactionWeights*  m_pWeightOverride;      // +0x78  reaction-weight override (NULL = none)
    uint64_t            m_rngState;             // +0x80  LCG state for the weighted pick
};
static_assert(sizeof(C_CombatAutomationDefense) == 0x88);

}  // namespace wh::combatmodule
