#pragma once

#include <cstdint>
#include "C_PerkList.h"
#include "E_RPGStat.h"
#include "E_RPGSkill.h"

// -----------------------------------------------
// Perk Subsystem -- stat or skill perk tracker
// -----------------------------------------------
// No RTTI name found (inlined structure)
// Constructor: S_ProgressionSubsystem::Ctor_1804A2090
// Re-init:     S_ProgressionSubsystem::ReInit_1804A1E7C
// AddStatXP:   S_ProgressionSubsystem::AddStatXP_18118F5F0
// Size: 0x260 per instance
//
// Two instances are embedded in S_SoulProgression (same type):
//   soul + 0x4A8 = m_activePerks — LIVE/runtime; holds BOTH stat AND skill levels + the
//                                  live perk-point counter (queried, XP'd, learned, saved).
//   soul + 0x750 = m_basePerks   — archetype-derived BASELINE; rebuilt from base stats +
//                                  perk/skill tables, then committed wholesale into
//                                  m_activePerks at create/reset/clone. See S_SoulProgression.h.
// NOTE: m_statLevels and m_skillLevels below BOTH live in EACH instance — a single
//       S_ProgressionSubsystem carries both arrays; the split is by array, not by instance.

namespace wh::rpgmodule {

class C_Soul;

struct S_ProgressionSubsystem {
    C_Soul*         m_pSoul;                // +0x000  parent soul pointer
    uint8_t         m_bInitialized;         // +0x008  flag (=1)
    char            _pad009[3];             // +0x009
    // Stat level/XP pairs — indexed by E_RPGStat (0..3 used: Strength/Agility/Vitality/Speech;
    // slots 4..9 reserved). Access: soul->m_perkMgmt.m_activePerks.m_statLevels[(int)E_RPGStat::X].level
    //   Confirmed in C_StatXPEffect::Apply reading *(soul + 8*stat_id + 0x4B4)
    struct S_StatEntry {
        uint32_t    level;      // current stat level
        uint32_t    xp;         // current XP within this level
    }               m_statLevels[10];       // +0x00C  (80 bytes, to +0x05C) — indexed by E_RPGStat

    int32_t         m_minPerkPoints;        // +0x05C  rpg_params[0x99] aka MinPerkPoints
    float           m_perkPointRate;        // +0x060  computed perk rate
    int32_t         m_maxPerkPoints;        // +0x064  rpg_params[0xD6] aka MaxPerkPoints
    int32_t         m_minLeftoverPerks;     // +0x068  rpg_params[0xA0] aka MinLeftoverPerks
    char            _pad06C[8];             // +0x06C
    uint32_t        m_counter;              // +0x074
    uint32_t        _pad078;                // +0x078
    uint32_t        _pad07C;                // +0x07C
    uint64_t        m_unk80;                // +0x080  init qword_183012A88
    void*           m_unkPtr88;             // +0x088
    uint8_t         m_unkByte90;            // +0x090
    char            _pad091[7];             // +0x091
    // Skill level/XP pairs — indexed by E_RPGSkill (33 entries, same {level,xp} layout as stat)
    S_StatEntry     m_skillLevels[33];      // +0x098  (264 bytes = 0x108) — indexed by E_RPGSkill (== Count)
    C_Soul*         m_pSoul2;              // +0x1A0
    char            _pad1A8[0x40];          // +0x1A8

    C_PerkList      m_perkList;             // +0x1E8  THE C_PerkList OBJECT
    // C_PerkList is 0x68 bytes, with vtable at +0x1E8
    // m_pPerkPoints pointer at +0x1E8 + 0x58 = +0x240

    float           m_playerOpinion;        // +0x250  per-NPC opinion-of-the-player, domain [-1,+1].
                                            //   active instance (soul+0x6F8) = current opinion: read sub_1802287D0
                                            //   (master-walk +0x480), written sub_1811F3224, the "player-npc" term of
                                            //   GetRelationship sub_180228414. base instance (soul+0x9A0) = archetype
                                            //   baseline, copied -> active by sub_1805A3F34. [VERIFIED; was m_unkDword250]
    uint32_t        _pad254;                // +0x254
    float           m_maxFloat;             // +0x258  init FLT_MAX (0x7F7FFFFF)
    uint32_t        _pad25C;                // +0x25C
};
static_assert(sizeof(S_ProgressionSubsystem) == 0x260);

}  // namespace wh::rpgmodule
