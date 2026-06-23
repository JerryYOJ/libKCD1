#pragma once

#include <cstdint>

namespace wh::combatmodule {

// ---------------------------------------------------------------------------
// S_ReactionWeights -- melee-defense reaction weight set (one float per reaction).
//
// Each defense tick the defender picks ONE of these five mutually-exclusive
// reactions by a weighted-random draw (picker sub_1805F9408). When used as an
// OVERRIDE (C_CombatAutomationDefense::m_pWeightOverride), a value < 0 means
// "leave the RPG-computed default for this slot"; a value >= 0 REPLACES that
// slot's weight (overlay sub_1805FA35C). Set a slot to 0.0 to forbid the
// reaction, or to a positive weight to bias toward it.
//
// Order matches the <MeleeDefenseAutomationControls/> BT node attributes
// (NoBlock/NormalBlock/PerfectBlock/SpecialPerfectBlock/Dodge) and the
// meleeDefenseAutomationControlsType brain-variable members. Layout verified
// from the setter sub_1804F83C8 (copies 0x14 bytes) and overlay sub_1805FA35C.
// ---------------------------------------------------------------------------
struct S_ReactionWeights {
    float noBlock;              // +0x00  do nothing (take the hit)
    float normalBlock;         // +0x04  ordinary directional block
    float perfectBlock;        // +0x08  perfect block
    float specialPerfectBlock; // +0x0C  master strike (riposte perfect block)
    float dodge;               // +0x10  dodge
};
static_assert(sizeof(S_ReactionWeights) == 0x14);

}  // namespace wh::combatmodule
