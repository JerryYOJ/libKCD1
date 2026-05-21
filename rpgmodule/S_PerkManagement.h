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

    S_PerkSubsystem     m_statPerks;            // +0x0D8  (stat perk subsystem, size 0x260)
    // Access: soul+0x4A8 = soul+0x3D0+0xD8
    //   stat levels: soul+0x4B4 = m_statPerks.m_statLevels[0]

    // Gap between subsystems
    uint64_t            m_gapVec[8];            // +0x338  (zeroed, 8 QWORDs)
    float               m_xpMultiplier;         // +0x378  (init 1.0f)
    float               m_maxFloat;             // +0x37C  (init FLT_MAX = 0x7F7FFFFF)

    S_PerkSubsystem     m_skillPerks;           // +0x380  (skill perk subsystem, size 0x260)
    // Access: soul+0x750 = soul+0x3D0+0x380

    S_DialogParams      m_dialogParams;         // +0x5E0  dialog/interaction state
};
static_assert(sizeof(S_PerkManagement) == 0x670);
// Flag at +0x5C8 relative: *(byte*)(this+0x5C8) |= 2  (skill C_PerkList flags)

}  // namespace wh::rpgmodule
