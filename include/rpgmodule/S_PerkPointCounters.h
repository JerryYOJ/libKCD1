#pragma once

#include <cstdint>

// -----------------------------------------------
// Perk Point Counter Structure (heap-allocated)
// -----------------------------------------------
// Size: 0x68 bytes (confirmed: CryMalloc(0x68) in AllocPerkPoints_1806D6F04)
// Pointed to by: C_PerkList::m_pPerkPoints (+0x58)
// Equivalent soul offset: *(soul + 0x6E8)
//
// Index formulas (verified from LearnPerk_181199EF4):
//   Stat perks:       2 * stat_id + 0x10
//   Skill perks:      2 * skill_id + 0x24
//   Main level perks: 0x66 (sentinel: stat=0xA, skill=0x21)
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

    // Stat perk points (WORD each). Only 0-3 used.
    uint16_t    statPoints[10];         // +0x10  [0]=STR [1]=AGI [2]=VIT [3]=SPC [4-9]=unused

    // Skill perk points (WORD each). Index = skill_id.
    // 0=stealth, 1=horse_riding, 2=fencing, 4=lockpicking,
    // 5=pickpocketing, 6=alchemy, 8=repairing, 13=drinking,
    // 14=hunter, 15=defense, 16=weapon_sword, 17=weapon_axe,
    // 18=weapon_bow, 21=weapon_mace, 24=weapon_unarmed,
    // 25=herbalism, 26=reading, 32=houndmaster
    uint16_t    skillPoints[33];        // +0x24

    // Main level perk points
    uint16_t    mainLevelPoints;        // +0x66
};
static_assert(sizeof(S_PerkPointCounters) == 0x68);

}  // namespace wh::rpgmodule
