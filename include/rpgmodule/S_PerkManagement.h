#pragma once

#include <cstdint>
#include <vector>
#include "S_PerkSubsystem.h"

// -----------------------------------------------
// Perk Management Container
// -----------------------------------------------
// No RTTI name found (inlined structure)
// Constructor: S_PerkManagement::Ctor_1804A1F54
// Lives at: soul + 0x3D0

namespace wh::rpgmodule {

// Polymorphic dialog/interaction tail embedded in S_PerkManagement at +0x5E0.
class S_DialogParams {
public:
    inline static constexpr auto RTTI = Offsets::RTTI_S_DialogParams;
    virtual ~S_DialogParams();

    uint32_t            m_dialogState;       // +0x08  (init 0)
    uint32_t            _pad0C;              // +0x0C
    uint64_t            m_dialogData[6];     // +0x10  (zeroed, to +0x40)
    C_Soul*             m_pDialogSoul;       // +0x40  (= soul, back-reference for dialog)
    uint64_t            m_unk48;             // +0x48  (zeroed)
    uint8_t             m_guidData[0x10];    // +0x50  (xmmword init from xmmword_1830130B8)
    uint64_t            m_tail[4];           // +0x60  (zeroed)
    uint32_t            m_tailFlag;          // +0x80  (init 0)
    uint32_t            _pad84;              // +0x84
    C_Soul*             m_pOwnerSoul;        // +0x88  (= soul, another back-reference)
};
static_assert(sizeof(S_DialogParams) == 0x90);

struct S_PerkManagement {
    // +0x000 to +0x0BF: set externally (not by this constructor)
    // Contains parent-soul chain pointer at +0x0B0 (soul+0x480)
    char                _pad000[0xB0];          // +0x000
    C_Soul*             m_pParentSoul;          // +0x0B0  parent soul for compound entities (walked by sub_18064D750)
    char                _padB8[0x08];           // +0x0B8

    // Perk definition vector (all available perks)
    std::vector<S_PerkDefinition*> m_perkDefs;  // +0x0C0  (begin/end/cap = 0x18 bytes)

    // ACTIVE (live, runtime) perk subsystem. Despite the historical "stat" name it holds
    // BOTH the stat levels (m_statLevels) AND the skill levels (m_skillLevels), plus the
    // single live perk-point counter. This is the instance gameplay reads/mutates:
    // C_Soul::GetActivePerkList (sub_1806FF460 -> soul+0x690), the perk-point recompute
    // (RepopulateAll wrapper sub_18119EFE0 -> soul+0x690), the level getter
    // (sub_1806837E4: stats via soul+0x4B4, skills via soul+0x540), stat-XP
    // (sub_1806AC280 -> soul+0x4B4) and LearnPerk (sub_18117E38C -> soul+0x6E8).
    // It is SEEDED from m_basePerks (see below) at create/reset/clone, and is the only
    // subsystem that is serialized (perkMgmt (de)serialize dispatcher sub_180AA4A90
    // case 0x92A targets perkMgmt+0xD8 only).
    S_PerkSubsystem     m_activeStats;          // +0x0D8  (size 0x260)
    // Access: soul+0x4A8 = soul+0x3D0+0xD8
    //   stat levels:  soul+0x4B4 = m_activeStats.m_statLevels[0]
    //   skill levels: soul+0x540 = m_activeStats.m_skillLevels[0]
    //   perk-point counter: soul+0x6E8 = m_activeStats.m_perkList.m_pPerkPoints

    // Gap between subsystems
    uint64_t            m_gapVec[8];            // +0x338  (zeroed, 8 QWORDs)
    float               m_xpMultiplier;         // +0x378  (init 1.0f)
    float               m_maxFloat;             // +0x37C  (init FLT_MAX = 0x7F7FFFFF)

    // BASE/recompute-staging perk subsystem (same type as m_activePerks). VERIFIED 2026-06.
    // Holds the character's archetype-derived BASELINE stats/skills/perks. The engine
    // rebuilds it from scratch (sub_1811F7FB0) out of the soul's base-stat container
    // (soul+0x2AC), its archetype/preset GUID (soul+0x168), and the global perk/skill
    // definition tables (qword_1835AC728+0x590/+0x598/+0x5A0); it is then copied WHOLESALE
    // into m_activePerks (sub_1805A3F34(soul+0x4A8 <- soul+0x750), reading every field of
    // m_basePerks). This populate-then-commit runs on soul create/bind
    // (FindOrCreateSoulByEntity_18030E510), reset-to-baseline (sub_1811FBB98), bulk reset
    // (sub_180AA43E0/sub_180AA0DC0) and on-load (sub_1811F8FF4 -> sub_1811F3E48). It is also
    // deep-copied as a first-class member on soul clone (sub_1805A3E00 <- sub_18030EABC).
    // It is NEVER serialized (recomputed on load) and never the queried/active subsystem.
    // Its perk-point counter is not allocated via the enable helper — the no-op
    // sub_1811F79A8(soul+0x750, 0) — its C_PerkList is populated directly during the rebuild.
    // (Was previously mislabeled "m_skillPerks".)
    S_PerkSubsystem     m_basePerks;            // +0x380  (size 0x260)
    // Access: soul+0x750 = soul+0x3D0+0x380

    S_DialogParams      m_dialogParams;         // +0x5E0  dialog/interaction state
};
static_assert(sizeof(S_PerkManagement) == 0x670);
// Flag at +0x5C8 relative: *(byte*)(this+0x5C8) |= 2  (m_basePerks' C_PerkList flags, set at ctor)

}  // namespace wh::rpgmodule
