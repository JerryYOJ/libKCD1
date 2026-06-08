#pragma once

#include <cstdint>
#include "E_RPGStat.h"
#include "E_RPGSkill.h"

// -----------------------------------------------
// Perk Point Counter Structure (heap-allocated)
// -----------------------------------------------
// Size: 0x68 bytes (confirmed: CryMalloc(0x68) in AllocPerkPoints_1806D6F04)
// Pointed to by: C_PerkList::m_pPerkPoints (+0x58)
// Equivalent soul offset: *(soul + 0x6E8)
//
// Index formulas (verified from LearnPerk_181199EF4):
//   Stat perks:       2 * (E_RPGStat)stat_id   + 0x10
//   Skill perks:      2 * (E_RPGSkill)skill_id + 0x24
//   Main level perks: 0x66 (sentinel: stat=0xA=E_RPGStat::Count?, skill=0x21=E_RPGSkill::Count)
//
// Increment: C_PerkList::StatXPVisitorOp_180A9AD90
//            (RTTI: _Func_impl_no_alloc<lambda, void, C_StatXPEffect const &>::operator())
// Decrement: S_PerkPointCounters::LearnPerk_181199EF4
//            (called from C_LearnPerkEffect::Apply_18117E38C, RTTI-verified)
//
// Other key functions:
//   ResetCounters_1806C4CA8    — zeros all stat/skill/mainLevel counters
//   RepopulateAll_18119F0E0    — resets then recomputes all counters from current levels
//   RepopulateSkills_180A93000 — loops skills 0-32, computes perk points per skill
//   CalcPointsFromLevel_181175AF0 — perk-points-from-XP formula using RPG params

namespace wh::rpgmodule {

class C_PerkList;

struct S_PerkPointCounters {
    uint8_t     _flag00;                // +0x00  initialized to 0, purpose unknown
    char        _pad01[7];              // +0x01
    C_PerkList* m_pOwnerPerkList;       // +0x08  back-pointer (set during allocation)

    // Stat perk points (WORD each). Indexed by E_RPGStat (0..3 used: STR/AGI/VIT/SPC; 4..9 unused).
    uint16_t    statPoints[10];         // +0x10

    // Skill perk points (WORD each). Indexed by E_RPGSkill (full 33-entry id->name in E_RPGSkill.h,
    // VERIFIED from rpg/skill.xml: 0 Stealth, 1 HorseRiding, 2 Fencing, ... 32 Houndmaster).
    uint16_t    skillPoints[33];        // +0x24

    // Main level perk points
    uint16_t    mainLevelPoints;        // +0x66
};
static_assert(sizeof(S_PerkPointCounters) == 0x68);

}  // namespace wh::rpgmodule
