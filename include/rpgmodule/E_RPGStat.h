#pragma once

#include <cstdint>

// ===========================================================================
// wh::rpgmodule::E_RPGStat  -  the 4 main character stats (stat_id).
// ===========================================================================
// Index into S_PerkSubsystem::m_statLevels (soul+0x4B4) and S_PerkPointCounters::statPoints.
// Accessed as *(soul + 8*stat_id + 0x4B4) (C_StatXPEffect::Apply) and base value via
// GetModifiedStatValue -> sub_180229950.
//
// SOURCE/CONFIDENCE: there is no `stat` table in Tables.pak (unlike rpg/skill.xml), and no
// clean stat-name code registry was found in the binary (the strength/agility/vitality/speech
// .rodata strings are UI/flash literals, not an ordered id table). The id->name mapping below
// is the established KCD main-stat set, consistent with the prior RE in S_PerkPointCounters.h
// ([0]=STR [1]=AGI [2]=VIT [3]=SPC). Names are [LIKELY] (KCD-known), ids are VERIFIED from usage.
//
// NOTE: the backing arrays reserve 10 slots (m_statLevels[10] / statPoints[10]); only ids
// 0..3 are used, 4..9 are reserved/unused.
// ===========================================================================

namespace wh::rpgmodule {

enum class E_RPGStat : int32_t {
    Strength  = 0,
    Agility   = 1,
    Vitality  = 2,
    Speech    = 3,

    Count     = 4,   // number of real main stats (the array still reserves 10 slots)
};

}  // namespace wh::rpgmodule
