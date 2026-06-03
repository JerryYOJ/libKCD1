#pragma once

#include <cstdint>
#include <vector>

// -----------------------------------------------
// C_PerkList -- Per-soul learned perk container
// -----------------------------------------------
// RTTI: .?AVC_PerkList@rpgmodule@wh@@
// vtable: 0x1821b0ea8  (1 virtual method only)
// Constructor: within S_PerkSubsystem::Ctor_1804A2090 (at subsystem + 0x1E8)
// Destructor:  C_PerkList::Dtor_1804A2C3C  (NON-virtual)
//
// Active instance lives at: soul + 0x690  (inside m_activePerks; the one GetActivePerkList returns,
//                                          holding the live learned/candidate perks + the live counter)
// Base instance lives at:   soul + 0x938  (inside m_basePerks — the archetype baseline; its perks are
//                                          repopulated during the base->active recompute and copied into
//                                          the active list via sub_18044A8F0, not allocated via the enable helper)
//
// Key methods (RTTI-verified):
//   RecalcPerkPoints_1805D2C74  — vfunc[0], creates C_StatXPEffect + C_SkillXPEffect
//                                  visitor lambdas to recompute perk points
//   Dtor_1804A2C3C              — frees S_PerkPointCounters, clears vectors, unregisters
//   AllocPerkPoints_1806D6F04   — CryMalloc(0x68), sets m_pPerkPoints
//   Reset_1804A2D64             — clears learned/candidate perks and resets counters
//   UpdateCandidatePerks_18044AB28 — iterates perk defs, checks eligibility
//   AddLearnedPerk_18044AA04    — adds perk to learned list (no point cost)
//   HasPerk_18044A298           — checks if perk GUID is already learned
//   FindPerkDef_18044B004       — binary-searches global perk definitions by GUID

namespace wh::rpgmodule {

struct S_PerkDefinition;
struct S_PerkPointCounters;

class C_PerkList {
public:
    // vfunc[0]: creates stat/skill XP visitor lambdas for perk point recalculation
    virtual void RecalcPerkPoints(void* pDispatcher);   // RecalcPerkPoints_1805D2C74

    void*                               m_pParent;          // +0x08
    std::vector<S_PerkDefinition*>      m_learnedPerks;     // +0x10
    std::vector<S_PerkDefinition*>      m_candidatePerks;   // +0x28
    std::vector<S_PerkDefinition*>      m_activePerks;      // +0x40

    S_PerkPointCounters* m_pPerkPoints;         // +0x58 <- THE PERK POINT COUNTER STRUCT

    uint8_t             m_flags;                // +0x60 (bit 0: locked, bit 2: registered)
    char                _pad61[7];              // +0x61
};
static_assert(sizeof(C_PerkList) == 0x68);

}  // namespace wh::rpgmodule
